//
// Created by seb on 15/02/23.
//

#include "server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE_PADDING_SIZE 5


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


}

Server::~Server() {
    terminate();
}

void Server::terminate() {
    for (int client_socket : client_sockets)
        close(client_socket);

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

    }

    client_sockets.push_back(client_socket);

    return client_socket;
}

bool Server::receiveData(int client_socket, char* buffer)
{
    // Receive data from the client
    size_t num_bytes = read(client_socket, buffer, sizeof(buffer));
    std::cout << "Received " << num_bytes << " bytes from client: " << buffer << "\n";

    return num_bytes > 0;
}

bool Server::sendData(int client_socket, const char* message)
{
    // Send a response to the client
    if (write(client_socket, message, strlen(message)) < 0) {
        std::cerr << "Error sending message to client\n";
        // TODO exception
        return false;
    }
    return true;
}
