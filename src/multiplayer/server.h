//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_SERVER_H
#define TETRIS_SERVER_H


#include <vector>
#include <string>
#include "../game.h"
#include "player.h"
#include "communicator.h"

class Server {

public:
    /**
     * start a socket at 127.0.0.1:2001
     */
    explicit Server(Game& g);

    /**
     * start the server
     */
    void start();

    /**
     * Close all sockets
     */
    ~Server();

private:
    /**
     * The server socket
     */
    int server_socket;

    /**
     * The list of connected clients
     */
    std::vector<Player> clients;

    /**
     * Wait until client tries to connectToServer and accept the connection
     * @return the client socket
     */
    void acceptPlayer();


    /**
     * Try to read a message on every sockets
     */
    void receiveAllMsg();

    /**
     * Broadcasts data to all client sockets except client_socket
     * @param message
     * @param client_socket
     * @return
     */
    bool broadcastData(std::vector<char>& message, int client_socket = -1);

    Game& game;

    std::thread acceptNewPlayerThread;
    std::thread receiveMsgThread;
};


#endif //TETRIS_SERVER_H
