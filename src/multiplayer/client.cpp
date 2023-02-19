//
// Created by seb on 15/02/23.
//

#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


Client::Client(char ip[], char name[]) : self(client_socket) {
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

    self.setName(name);

    char *c = self.toData();
    // TODO sendData();
}

Client::~Client() {
    terminate();
}

void Client::terminate() const {
    close(client_socket);
}
