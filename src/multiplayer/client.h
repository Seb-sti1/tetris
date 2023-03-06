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

    void connectToServer(std::string ip, std::string name);

    ~Client();

    /**
     * The list of connected clients
     */
    std::vector<Player*> clients;

    /**
     * The player object of the client
     */
    Player self;
private:
    /**
     * the socket of the client to communicate with the server
     */
    int client_socket;

    /**
     * Receive a message from a client_socket
     * @return a message was successfully received
     */
    void receiveMsg();

    /**
     * The thread to receive message from clients
     */
    std::thread receiveMsgThread;

    /**
     * While the connection is on
     */
    bool running = true;

    /**
     * The game ref
     */
    Game &game;
};


#endif //TETRIS_CLIENT_H
