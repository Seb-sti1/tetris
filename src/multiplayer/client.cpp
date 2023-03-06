//
// Created by seb & billy on 15/02/23.
//

#include "client.h"
#include "messages/disconnect.h"
#include "messages/gamestart.h"
#include <iostream>
#include <utility>
#include <arpa/inet.h>
#include <unistd.h>


Client::Client(Game& g) : game(g), self(client_socket) {}

void Client::connectToServer(std::string ip, std::string name)
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        throw std::system_error(errno, std::system_category(), "Failed to create socket.");
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());  // loopback address for testing on same machine
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2001);
    if (connect(client_socket, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to serverAddr" << std::endl;
        throw std::system_error(errno, std::system_category(), "Failed to connect to server.");
    }

    std::cout << "Connected to server" << std::endl;

    self.setName(std::move(name));

    com::sendMsg(client_socket, self);

    receiveMsgThread = std::thread(&Client::receiveMsg, this);
    receiveMsgThread.detach();
}

Client::~Client() {
    running = false;
    close(client_socket);
}

void Client::receiveMsg()
{
    while (running)
    {
        while (!com::dataPresent(client_socket)) {}

        std::vector<char> msg_size_as_char(SIZE_OF_MESSAGE_SIZE);
        com::receiveData(client_socket, msg_size_as_char);

        std::vector<char> msg_type_as_char(1);
        com::receiveData(client_socket, msg_type_as_char);

        int msg_size = atoi(msg_size_as_char.data());
        auto msg_type = static_cast<messageType>((int) msg_type_as_char.at(0));

        std::vector<char> buffer(msg_size - SIZE_OF_MESSAGE_SIZE - 1);
        com::receiveData(client_socket, buffer);

        switch (msg_type) {
            case GAME_START: {
                auto gs = GameStart();
                gs.deserialize(buffer);

                game.startGame(gs.seed);
                break;
            }
            case PLAYER_DATA: {
                auto new_player = new Player(client_socket);
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
                com::sendMsg(client_socket, self);

                break;
        }
    }
}
