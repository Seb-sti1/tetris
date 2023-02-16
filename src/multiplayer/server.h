//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_SERVER_H
#define TETRIS_SERVER_H


#include <vector>
#include <string>
#include "../game.h"

class Server {

public:
    /**
     * Start a socket at 127.0.0.1:2001
     */
    Server(Game& g);

    /**
     * Close all sockets
     */
    ~Server();

    /**
     * Close all sockets
     */
    void terminate();

private:
    /**
     * The server socket
     */
    int server_socket;

    /**
     * The list of connected clients
     */
    std::vector<int> client_sockets;

    /**
     * Wait until client tries to connect and accept the connection
     * @return the client socket
     */
    int acceptPlayer();

    /**
     * Send data to a client socket
     * @param client_socket the client socket
     * @param message the data to send
     * @return if the data was sent
     */
    bool sendData(int client_socket, const char* message);

    bool receiveData(int client_socket, char* buffer);

    Game& game;
};


#endif //TETRIS_SERVER_H
