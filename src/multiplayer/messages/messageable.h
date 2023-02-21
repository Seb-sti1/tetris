//
// Created by seb on 19/02/23.
//

#ifndef TETRIS_MESSAGEABLE_H
#define TETRIS_MESSAGEABLE_H

#include <vector>

enum messageType {GAME_START, PLAYER_DATA, NEW_PLAYER, DISCONNECT, GET_PLAYER_DATA, UNKNOWN};

#define SIZE_OF_MESSAGE_SIZE 4

class messageable {

public:
    void toData(std::vector<char> &data);
    virtual void serialize(std::vector<char> &data) = 0;
    virtual void deserialize(std::vector<char> data) = 0;
    virtual messageType getType();
};


#endif //TETRIS_MESSAGEABLE_H
