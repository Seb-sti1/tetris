//
// Created by seb & billy on 28/02/23.
//

#ifndef TETRIS_COMMUNICATOR_H
#define TETRIS_COMMUNICATOR_H

#include <sys/socket.h>
#include <iostream>
#include "messages/messageable.h"

namespace com {

    /**
     * Send data to a socket
     * @param socket the socket
     * @param msg the buffer
     * @return if it was sent
     */
    void sendMsg(int socket, Messageable& msg) noexcept(false);

    /**
     * @param socket the socket
     * @return If there is data to read
     */
    bool dataPresent(int socket);

    /**
     * Read data from a socket
     * @param socket the socket to read from to
     * @param buffer the data buffer
     */
    void receiveData(int socket, std::vector<char>& buffer) noexcept(false);
}


#endif //TETRIS_COMMUNICATOR_H
