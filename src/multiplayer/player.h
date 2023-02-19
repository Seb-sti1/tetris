//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_PLAYER_H
#define TETRIS_PLAYER_H


#include "messages/messageable.h"

class Player : messageable {

public:
    implicit Player(int client_socket);


    char* name;

    unsigned level;
    unsigned score;
    unsigned completedLines;
    bool alive;

    int serialize(char data);
    void deserialize(char* data);

private:
    int client_socket;


};


#endif //TETRIS_PLAYER_H
