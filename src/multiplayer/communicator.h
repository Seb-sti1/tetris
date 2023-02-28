//
// Created by seb on 28/02/23.
//

#ifndef TETRIS_COMMUNICATOR_H
#define TETRIS_COMMUNICATOR_H

#include <sys/socket.h>
#include <iostream>

namespace com {
    bool sendData(int socket, std::vector<char>& data);

    bool receiveData(int socket, std::vector<char>& buffer);
}


#endif //TETRIS_COMMUNICATOR_H
