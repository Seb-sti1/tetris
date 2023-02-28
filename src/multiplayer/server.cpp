//
// Created by seb on 15/02/23.
//

#include "server.h"
#include "messages/messageable.h"
#include "messages/disconnect.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


Server::Server(Game& g) : game(g) {
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

    acceptPlayer();
    // TODO thread accepting/receiving sockets
}

Server::~Server() {
    for (const auto& client : clients)
        close(client.client_socket);

    close(server_socket);
}

int Server::acceptPlayer() {
    int client_socket;
    sockaddr_in client_address{};

    // Accept incoming connections
    socklen_t client_address_size = sizeof(client_address);
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size)) < 0) {
        std::cerr << "Error accepting connection\n";
        // TODO exception
        return -1;
    }

    std::cout << "New client connected!\n";

    if (game.state != WAITING)
    {
        receiveMsg(client_socket);
    }
    else
    {
        receiveMsg(client_socket); // TODO remove

        Disconnect packet("La partie a déjà commencée !");

        std::vector<char> data;
        packet.toData(data);

        com::sendData(client_socket, data);
    }

    return client_socket;
}

bool Server::receiveMsg(int socket)
{
    std::vector<char> msg_size_as_char(SIZE_OF_MESSAGE_SIZE);
    com::receiveData(socket, msg_size_as_char);

    std::vector<char> msg_type_as_char(1);
    com::receiveData(socket, msg_type_as_char);

    int msg_size = atoi(msg_size_as_char.data());
    auto msg_type = static_cast<messageType>((int) msg_type_as_char.at(0));

    std::vector<char> buffer(msg_size - SIZE_OF_MESSAGE_SIZE - 1);
    com::receiveData(socket, buffer);

    switch (msg_type)
    {
        case PLAYER_DATA: {
            auto new_player = Player(socket);
            new_player.deserialize(buffer);

            std::cout << new_player.name << " send new information" << std::endl;

            // TODO update player & broadcast
            return true;
        }
        case NEW_PLAYER: {
            auto new_player = Player(socket);
            new_player.deserialize(buffer);

            std::cout << new_player.name << " joined the game !" << std::endl;

            clients.push_back(new_player);
            // TODO broadcast
            return true;
        }
    }

    return false;
}

bool Server::broadcastData(std::vector<char>& message, int client_socket)
{
    bool result = true;

    // Send message to every client except client_socket if given as an argument
    for (auto & client : clients)
    {
        if (client_socket != client.client_socket) {
            result = result and com::sendData(client.client_socket, message);
        }
    }

    return result;
}