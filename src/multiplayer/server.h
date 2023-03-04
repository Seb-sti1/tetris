//
// Created by seb & billy on 15/02/23.
//

#ifndef TETRIS_SERVER_H
#define TETRIS_SERVER_H


#include <vector>
#include <string>
#include "../game.h"
#include "messages/player.h"
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
     * stop the server
     */
     void stop();

    /**
     * Close all sockets
     */
    ~Server();

    /**
     * Send a game start packet
     * @param seed
     */
    void startGame(long seed);

private:
    /**
     * The server socket
     */
    int server_socket;

    /**
     * The list of connected clients
     */
    std::vector<Player*> clients;

    /**
     * Wait until client tries to connect and accept the connection
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
    bool broadcastData(Messageable& message, int client_socket = -1);

    /**
     * The thread to accept players continuously
     */
    std::thread acceptNewPlayerThread;

    /**
     * The thread to receive message from clients
     */
    std::thread receiveMsgThread;

    /**
     * If the server should continue accepting new client or receiving new message
     */
    bool running;

    /**
     * The player object of the client
     */
    Player self;

    /**
     * The game ref
     */
    Game& game;
};


#endif //TETRIS_SERVER_H
