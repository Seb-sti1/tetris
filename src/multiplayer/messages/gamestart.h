//
// Created by seb & billy on 01/03/23.
//

#ifndef TETRIS_GAMESTART_H
#define TETRIS_GAMESTART_H


#include <vector>
#include "messageable.h"

class GameStart : public Messageable {

public:
    explicit GameStart(long seed);
    GameStart() = default;

    long seed;

    void serialize(std::vector<char> &data) override;
    void deserialize(std::vector<char> data) override;
    messageType getType() override;

};


#endif //TETRIS_GAMESTART_H
