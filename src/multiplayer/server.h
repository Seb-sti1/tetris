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
     * Start a socket at 127.0.0.1:2001
     */
    explicit Server(Game& g);

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
     * Wait until client tries to connect and accept the connection
     * @return the client socket
     */
    int acceptPlayer();

    /**
     * Receive a message from a socket
     * @param socket the socket
     * @return a message was successfully received
     */
    bool receiveMsg(int socket);

    /**
     * Broadcasts data to all client sockets except client_socket
     * @param message
     * @param client_socket
     * @return
     */
    bool broadcastData(std::vector<char>& message, int client_socket = -1);

    Game& game;
};


#endif //TETRIS_SERVER_H
