//
// Created by seb & billy on 15/02/23.
//

#include "client.h"
#include "messages/disconnect.h"
#include "messages/gamestart.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


Client::Client(Game& g) : game(g), self(client_socket) {}

void Client::connectToServer(char ip[], char name[])
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        // TODO exception
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_addr.s_addr = inet_addr(ip);  // loopback address for testing on same machine
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2001);
    if (connect(client_socket, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
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

// TODO run in thread
bool Client::receiveMsg(int socket)
{
    while(!com::dataPresent(socket)) {}

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
        case GAME_START: {
            auto gs = GameStart();
            gs.deserialize(buffer);

            game.startGame(gs.seed);
            return true;
        }
        case PLAYER_DATA: {
            auto new_player = new Player(socket);
            new_player->deserialize(buffer);

            bool found = false;

            for (auto client : clients)
            {
                if (client->name == new_player->name)
                {
                    std::cout << "Updating " << new_player->name << std::endl;

                    client->update(new_player);

                    found = true;
                    break;
                }
            }

            if (!found && self.name != new_player->name)
            {
                std::cout << "New player " << new_player->name << std::endl;
                clients.push_back(new_player);
            }

            return true;
        }
        case DISCONNECT: {
            Disconnect packet{};
            packet.deserialize(buffer);

            std::cout << "The server has stopped : " << packet.reason << std::endl;

            // TODO show message & quit game

            return true;
        }
        case GET_PLAYER_DATA:
            self.update(game);
            com::sendMsg(client_socket, self);

            return true;
    }

    return false;
}
