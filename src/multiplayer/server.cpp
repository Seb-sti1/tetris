//
// Created by seb & billy on 15/02/23.
//

#include "server.h"
#include "messages/messageable.h"
#include "messages/disconnect.h"
#include "messages/gamestart.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


// TODO detect when a client disconnect (currently makes app crash)
// TODO deal with end of games
// TODO ping clients to update players data

Server::Server(Game& g) : game(g), self(tetro_socket) {}

void Server::connectToServer(std::string ip, std::string name)
{
    isServer = false;

    tetro_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (tetro_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        throw std::system_error(errno, std::system_category(), "Failed to create socket.");
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());  // loopback address for testing on same machine
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2001);
    if (connect(tetro_socket, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to serverAddr" << std::endl;
        throw std::system_error(errno, std::system_category(), "Failed to connect to server.");
    }

    std::cout << "Connected to server" << std::endl;

    self.setName(std::move(name));

    com::sendMsg(tetro_socket, self);

    receiveMsgThread = std::thread(&Server::receiveMsg, this);
    receiveMsgThread.detach();
}

void Server::startServer()
{
    isServer = true;
    running = true;

    sockaddr_in server_address{};

    if ((tetro_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Error creating socket\n";
        // TODO exception
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(2001);
    if (bind(tetro_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error binding socket\n";
        // TODO exception
    }

    // Listen for incoming connections
    if (listen(tetro_socket, 3) < 0) {
        std::cerr << "Error listening for connections\n";
        // TODO exception
    }

    std::cout << "Server listening on port 2001...\n";

    acceptNewPlayerThread = std::thread(&Server::acceptPlayer, this);
    acceptNewPlayerThread.detach();

    receiveMsgThread = std::thread(&Server::receiveAllMsg, this);
    receiveMsgThread.detach();
}

void Server::disconnectFromServer()
{
    running = false;
    close(tetro_socket);
}

void Server::stopServer()
{
    // stopServer listening and accepting
    running = false;

    // send a disconnect signal to every client
    Disconnect d;
    broadcastData(d);

    // close all the sockets
    for (auto client : clients)
        close(client->client_socket);

    close(tetro_socket);
}

Server::~Server() {
    if (isServer)
    {
        stopServer();
    }
    else
    {
        disconnectFromServer();
    }
}

void Server::acceptPlayer() {
    while (running)
    {
        int client_socket;
        sockaddr_in client_address{};

        // Accept incoming connections
        socklen_t client_address_size = sizeof(client_address);
        if ((client_socket = accept(tetro_socket, (struct sockaddr *) &client_address, &client_address_size)) < 0) {
            std::cerr << "Error accepting connection\n";
            // TODO exception
        }

        if (game.state == WAITING) {
            std::cout << "New client connected!\n";

            auto p = new Player(client_socket);

            clients.push_back(p);

            com::sendMsg(p->client_socket, self);
        } else {
            std::cout << "New client tried to connect but the game is already started!\n";

            Disconnect packet("La partie a déjà commencé !");
            com::sendMsg(client_socket, packet);
        }
    }
}

void Server::receiveAllMsg()
{
    while (running)
    {
        for (auto client : clients) // FIXME might be causing a segfault
        {
            if (com::dataPresent(client->client_socket))
            {
                std::vector<char> msg_size_as_char(SIZE_OF_MESSAGE_SIZE);
                com::receiveData(client->client_socket, msg_size_as_char);

                std::vector<char> msg_type_as_char(1);
                com::receiveData(client->client_socket, msg_type_as_char);

                int msg_size = atoi(msg_size_as_char.data());
                auto msg_type = static_cast<messageType>((int) msg_type_as_char.at(0));

                std::vector<char> buffer(msg_size - SIZE_OF_MESSAGE_SIZE - 1);
                com::receiveData(client->client_socket, buffer);

                if (msg_type == PLAYER_DATA)
                {
                    client->deserialize(buffer);

                    std::cout << client->name << " send new information" << std::endl;

                    broadcastData(*client, client->client_socket); // TODO check if working
                }
                else
                {
                    std::cout << client->name << " send a packet not useful for the server" << std::endl;
                }
            }
        }
    }
}


void Server::receiveMsg()
{
    while (running)
    {
        while (!com::dataPresent(tetro_socket)) {}

        std::vector<char> msg_size_as_char(SIZE_OF_MESSAGE_SIZE);
        com::receiveData(tetro_socket, msg_size_as_char);

        std::vector<char> msg_type_as_char(1);
        com::receiveData(tetro_socket, msg_type_as_char);

        int msg_size = atoi(msg_size_as_char.data());
        auto msg_type = static_cast<messageType>((int) msg_type_as_char.at(0));

        std::vector<char> buffer(msg_size - SIZE_OF_MESSAGE_SIZE - 1);
        com::receiveData(tetro_socket, buffer);

        switch (msg_type) {
            case GAME_START: {
                auto gs = GameStart();
                gs.deserialize(buffer);

                game.startGame(gs.seed);
                break;
            }
            case PLAYER_DATA: {
                auto new_player = new Player(tetro_socket);
                new_player->deserialize(buffer);

                bool found = false;

                for (auto client: clients) {
                    if (client->name == new_player->name) {
                        std::cout << "Updating " << new_player->name << std::endl;

                        client->update(new_player);

                        found = true;
                        break;
                    }
                }

                if (!found && self.name != new_player->name) {
                    std::cout << "New player " << new_player->name << std::endl;
                    clients.push_back(new_player);
                }

                break;
            }
            case DISCONNECT: {
                Disconnect packet{};
                packet.deserialize(buffer);

                std::cout << "The server has stopped : " << packet.reason << std::endl;

                // TODO show message & quit game

                break;
            }
            case GET_PLAYER_DATA:
                self.update(game);
                com::sendMsg(tetro_socket, self);

                break;
        }
    }
}


bool Server::broadcastData(Messageable& msg, int client_socket)
{
    bool result = true;

    // Send message to every client except tetro_socket if given as an argument
    for (auto client : clients)
    {
        if (client_socket != client->client_socket) {
            result = result and com::sendMsg(client->client_socket, msg);
        }
    }

    return result;
}

void Server::startGame(long seed) {
    auto msg = GameStart(seed);

    broadcastData(msg);
}
