//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_PLAYER_H
#define TETRIS_PLAYER_H


#include <string>
#include "messages/messageable.h"

class Player : public messageable {

public:
    explicit Player(int& client_socket);

    std::string name;

    unsigned level;
    unsigned score;
    unsigned completedLines;
    bool alive;

    void serialize(std::vector<char> &data) override;
    void deserialize(std::vector<char> data) override;
    messageType getType() override;

    void setName(char *string);

private:
    int& client_socket;


};


#endif //TETRIS_PLAYER_H
