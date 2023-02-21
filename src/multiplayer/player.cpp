//
// Created by seb on 15/02/23.
//

#include "player.h"

struct player {
    unsigned level;
    unsigned score;
    unsigned completedLines;
    bool alive;
    char name[];
};


Player::Player(int& client_socket) : client_socket(client_socket),
level(0), score(0), completedLines(0), alive(true) {}

void Player::serialize(std::vector<char> &data)
{
    data.resize(SIZE_OF_MESSAGE_SIZE + 1 + (name.size() + 1) +
                 + sizeof(level) + sizeof(score) + sizeof(completedLines) + sizeof(alive));

    auto* p = reinterpret_cast<player *>(data.data() + SIZE_OF_MESSAGE_SIZE + 1);

    p->level = 1;
    p->score = 2;
    p->completedLines = 3;
    p->alive = alive;
    for (int i = 0; i < name.size(); i++)
        p->name[i] = name[i];
    p->name[name.size()] = '\0';
}

void Player::deserialize(std::vector<char> data)
{
    auto* p = reinterpret_cast<player *>(data.data());

    level = p->level;
    score = p->score;
    completedLines = p->completedLines;
    alive = p->alive;
    name = p->name;
}

messageType Player::getType() {
    return PLAYER_DATA;
}

void Player::setName(char* n) {
    name = n;
}



