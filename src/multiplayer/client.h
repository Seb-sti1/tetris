//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_CLIENT_H
#define TETRIS_CLIENT_H


#include <string>
#include "player.h"

class Client {

public:
    explicit Client(char ip[], char name[]);

    ~Client();

    void terminate() const;

private:
    int client_socket;

    Player self;

};


#endif //TETRIS_CLIENT_H
