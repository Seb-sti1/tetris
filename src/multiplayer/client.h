//
// Created by seb & billy on 15/02/23.
//

#ifndef TETRIS_CLIENT_H
#define TETRIS_CLIENT_H


#include <string>
#include "messages/player.h"
#include "communicator.h"
#include "../game.h"

class Client {

public:
    explicit Client(Game& g);

    void connectToServer(char ip[], char name[]);

    ~Client();

private:
    int client_socket;

    /**
     * Receive a message from a socket
     * @param socket the socket
     * @return a message was successfully received
     */
    bool receiveMsg(int socket);

    Player self;

    Game &game;
};


#endif //TETRIS_CLIENT_H
