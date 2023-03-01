//
// Created by seb & billy on 01/03/23.
//

#include "gamestart.h"

struct gamestart {
    long seed;
};

GameStart::GameStart(long seed) : seed(seed) {}

void GameStart::serialize(std::vector<char> &data) {
    data.resize(SIZE_OF_MESSAGE_SIZE + 1 + sizeof(seed));

    auto* gs = reinterpret_cast<gamestart *>(data.data() + SIZE_OF_MESSAGE_SIZE + 1);

    gs->seed = seed;
}

void GameStart::deserialize(std::vector<char> data) {
    auto* gs = reinterpret_cast<gamestart *>(data.data());

    seed = gs->seed;
}

messageType GameStart::getType() {
    return GAME_START;
}

