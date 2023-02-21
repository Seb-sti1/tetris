//
// Created by seb on 15/02/23.
//

#include "server.h"
#include "player.h"
#include "messages/messageable.h"
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

    acceptPlayer();

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

    //if (game.state != WAITING)
    //{

    receiveMsg(client_socket);
    //}

    client_sockets.push_back(client_socket);

    return client_socket;
}

bool Server::receiveData(int client_socket, std::vector<char> &buffer)
{
    // Receive data from the client
    size_t num_bytes = recv(client_socket, buffer.data(), buffer.size(), 0);
    std::cout << "Received " << num_bytes << " bytes from client\n";

    return num_bytes > 0;
}

bool Server::receiveMsg(int client_socket)
{
    std::vector<char> msg_size_as_char(SIZE_OF_MESSAGE_SIZE);
    receiveData(client_socket, msg_size_as_char);

    std::vector<char> msg_type_as_char(1);
    receiveData(client_socket, msg_type_as_char);

    int msg_size = atoi(msg_size_as_char.data());
    auto msg_type = static_cast<messageType>((int) msg_type_as_char.at(0));

    std::vector<char> buffer(msg_size - SIZE_OF_MESSAGE_SIZE - 1);
    receiveData(client_socket, buffer);

    switch (msg_type)
    {
    case GAME_START:
        
        /* code */
        break;
    case PLAYER_DATA: {
            auto new_player = Player(client_socket);
            new_player.deserialize(buffer);

            std::cout << new_player.name << std::endl;

            return  true;
        break;
    }
    case NEW_PLAYER:
        //Player new_player(client_socket);
        //new_player.deserialize(msg_size, &buffer[SIZE_OF_MESSAGE_SIZE+2]);
        break;
    case DISCONNECT:
        break;
    case GET_PLAYER_DATA:
        
        break;
    case UNKNOWN:
        /* code */
        break;
    }

    return false;
}

bool Server::sendData(int client_socket, const char* message)
{
    // Send a response to the client
    if (send(client_socket, message, strlen(message), 0) < 0) {
        std::cerr << "Error sending message to client\n";
        // TODO exception
        return false;
    }
    return true;
}

bool Server::broadcastData(const char* message, int client_socket)
{
    bool result = true;
    // Send message to every client except client_socket if given as an argument
    for (int socket_idx=0; (socket_idx<client_sockets.size()) && (client_sockets[socket_idx]!=client_socket); socket_idx++)
    {
        result = result and sendData(client_sockets[socket_idx], message);
    }

    return result;
}