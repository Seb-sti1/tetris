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
// TODO merge server/client ? (lot a of thing in common : thread, send/receive, player list...)
// TODO deal with end of games

Server::Server(Game& g) : game(g), self(server_socket) {}

void Server::start()
{
    running = true;

    sockaddr_in server_address{};

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Error creating socket\n";
        // TODO exception
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(2001);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error binding socket\n";
        // TODO exception
    }

    // Listen for incoming connections
    if (listen(server_socket, 3) < 0) {
        std::cerr << "Error listening for connections\n";
        // TODO exception
    }

    std::cout << "Server listening on port 2001...\n";

    acceptNewPlayerThread = std::thread(&Server::acceptPlayer, this);
    acceptNewPlayerThread.detach();

    receiveMsgThread = std::thread(&Server::receiveAllMsg, this);
    receiveMsgThread.detach();
}

void Server::stop()
{
    running = false;

    for (auto client : clients)
        close(client->client_socket);

    close(server_socket);
}

Server::~Server() {
    stop();
}

void Server::acceptPlayer() {
    while (running)
    {
        int client_socket;
        sockaddr_in client_address{};

        // Accept incoming connections
        socklen_t client_address_size = sizeof(client_address);
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size)) < 0) {
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

            std::vector<char> data;
            packet.toData(data);

            com::sendData(client_socket, data);
        }
    }
}

void Server::receiveAllMsg()
{
    while (running)
    {
        for (auto client : clients)
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


bool Server::broadcastData(Messageable& msg, int client_socket)
{
    bool result = true;

    // Send message to every client except client_socket if given as an argument
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
