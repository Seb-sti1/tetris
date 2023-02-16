//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_CLIENT_H
#define TETRIS_CLIENT_H


#include <string>

class Client {

public:
    Client(char* ip);

    ~Client();

    void terminate();

private:
    int client_socket;

};


#endif //TETRIS_CLIENT_H
