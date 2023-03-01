//
// Created by seb on 15/02/23.
//

#include "client.h"
#include "messages/disconnect.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


Client::Client(Game &g, char ip[], char name[]) : game(g), self(client_socket) {
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

    com::sendMsg(client_socket, self);

    receiveMsg(client_socket);
}

Client::~Client() {
    close(client_socket);
}


bool Client::receiveMsg(int socket)
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
        case GAME_START:

            /* code */
            break;
        case PLAYER_DATA: {
            auto new_player = Player(socket);
            new_player.deserialize(buffer);

            std::cout << new_player.name << std::endl;

            return true;
        }
        case NEW_PLAYER:
            //Player new_player(socket);
            //new_player.deserialize(msg_size, &buffer[SIZE_OF_MESSAGE_SIZE+2]);
            break;
        case DISCONNECT: {
            Disconnect packet{};
            packet.deserialize(buffer);

            std::cout << "Kill client : " << packet.reason << std::endl;

            return true;
        }
        case GET_PLAYER_DATA:
            self.update(game);
            com::sendMsg(client_socket, self);

            return true;
        case UNKNOWN:
            /* code */
            break;
    }

    return false;
}
