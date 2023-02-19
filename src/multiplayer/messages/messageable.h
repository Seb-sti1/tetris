//
// Created by seb on 19/02/23.
//

#ifndef TETRIS_MESSAGEABLE_H
#define TETRIS_MESSAGEABLE_H

enum messageType {GAME_START, PLAYER_DATA, NEW_PLAYER, DISCONNECT, GET_PLAYER_DATA, UNKNOWN};

#define SIZE_OF_MESSAGE_SIZE 4

class messageable {

    char* toData();
    virtual int serialize(char* data);
    virtual void deserialize(char* data);

private:
    messageType type;

};


#endif //TETRIS_MESSAGEABLE_H
