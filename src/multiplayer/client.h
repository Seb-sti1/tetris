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
    /**
     * the socket of the client to communicate with the server
     */
    int client_socket;

    /**
     * The list of connected clients
     */
    std::vector<Player*> clients;

    /**
     * Receive a message from a socket
     * @param socket the socket
     * @return a message was successfully received
     */
    bool receiveMsg(int socket);
    
    /**
     * The thread to receive message from clients
     */
    std::thread receiveMsgThread;

    /**
     * The player object of the client
     */
    Player self;

    /**
     * The game ref
     */
    Game &game;
};


#endif //TETRIS_CLIENT_H
