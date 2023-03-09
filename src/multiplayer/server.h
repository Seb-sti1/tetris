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
     * startServer a socket at 127.0.0.1:2001
     */
    explicit Server(Game& g);

    /**
     * Connect to the server
     * @param ip the ip
     * @param name the name of the player
     */
    void connectToServer(std::string ip, std::string name);

    /**
     * Disconnect from the server
     */
    void disconnectFromServer();

    /**
     * startServer the server
     */
    void startServer();

    /**
     * stopServer the server
     */
     void stopServer();

    /**
     * Close all sockets
     */
    ~Server();

    /**
     * Send a game startServer packet
     * @param seed
     */
    void startGame(long seed);

    /**
     * The list of connected clients
     */
    std::vector<Player*> clients;

    /**
     * The player object of the client
     */
    Player self;

    /**
     * If the object is a server or a client
     */
    bool isServer = false;

/**
 * If the server should continue accepting new client or receiving new message
 */
bool running = false;
private:
    /**
     * The server or client socket
     */
    int tetro_socket;

    /**
     * accept new client and read a message on every existing (alive) clients
     */
    void acceptClientAndReceiveAllMsg();

    /**
     * Read messages from a server
     */
    void receiveMsg();

    /**
     * Broadcasts data to all client sockets except tetro_socket
     * @param message
     * @param client_socket
     * @return
     */
    bool broadcastData(Messageable& message, int client_socket = -1);

    /**
     * actualize player list
     */
    void actualizePlayers();

    /**
     * The thread to receive message and on server side accept clients
     */
    std::thread serverThread;

    /**
     * The game ref
     */
    Game& game;
};


#endif //TETRIS_SERVER_H
