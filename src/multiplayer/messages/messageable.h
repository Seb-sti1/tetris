//
// Created by seb on 19/02/23.
//

#ifndef TETRIS_MESSAGEABLE_H
#define TETRIS_MESSAGEABLE_H

#include <vector>

enum messageType {GAME_START, PLAYER_DATA, NEW_PLAYER, DISCONNECT, GET_PLAYER_DATA, UNKNOWN};

#define SIZE_OF_MESSAGE_SIZE 4

class Messageable {
public:
    virtual messageType getType();

    void toData(std::vector<char> &data);

private:
    virtual void serialize(std::vector<char> &data) = 0;
    virtual void deserialize(std::vector<char> data) = 0;
};


#endif //TETRIS_MESSAGEABLE_H
