//
// Created by seb & billy on 28/02/23.
//

#ifndef TETRIS_COMMUNICATOR_H
#define TETRIS_COMMUNICATOR_H

#include <sys/socket.h>
#include <iostream>
#include "messages/messageable.h"

namespace com {
    bool sendMsg(int socket, Messageable& msg);

    /**
     * @param socket the socket
     * @return If there is data to read
     */
    bool dataPresent(int socket);

    bool receiveData(int socket, std::vector<char>& buffer);
}


#endif //TETRIS_COMMUNICATOR_H
