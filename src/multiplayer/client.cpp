//
// Created by seb on 15/02/23.
//

#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>


Client::Client(char* ip) {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        // TODO exception
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_addr.s_addr = inet_addr(ip);  // loopback address for testing on same machine
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2001);
    if (connect(client_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to serverAddr" << std::endl;
        // TODO exception
    }


    std::cout << "Connected to server" << std::endl;

    // send data to the server
    std::string message = "Hello, server!";
    if (send(client_socket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Failed to send data" << std::endl;
        // TODO exception
    }

    std::cout << "Data sent to server: " << message << std::endl;

    // receive data from the server
    char buffer[1024] = {0};
    if (recv(client_socket, buffer, sizeof(buffer), 0) < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        // TODO exception
    }

    std::cout << "Data received from server: " << buffer << std::endl;
}

Client::~Client() {
    terminate();
}

void Client::terminate() {
    close(client_socket);
}
