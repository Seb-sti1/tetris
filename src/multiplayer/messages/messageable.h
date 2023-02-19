//
// Created by seb on 19/02/23.
//

#ifndef TETRIS_MESSAGEABLE_H
#define TETRIS_MESSAGEABLE_H

enum messageType {GAME_START, PLAYER_DATA, NEW_PLAYER, DISCONNECT, GET_PLAYER_DATA, UNKNOWN};

#define SIZE_OF_MESSAGE_SIZE 4

class messageable {

public:
    char* toData();
    virtual int serialize(char* data) = 0;
    virtual void deserialize(int size, char* data) = 0;
    virtual messageType getType();
};


#endif //TETRIS_MESSAGEABLE_H
