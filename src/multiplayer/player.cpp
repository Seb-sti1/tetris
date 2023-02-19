//
// Created by seb on 15/02/23.
//

#include "player.h"

struct player {
    char* name;
    unsigned level;
    unsigned score;
    unsigned completedLines;
    bool alive;
};


Player::Player(int& client_socket) : client_socket(client_socket),
level(0), score(0), completedLines(0), alive(true) {}

int Player::serialize(char *data)
{
    auto* p = new player;

    p->name = name;
    p->level = level;
    p->score = score;
    p->completedLines = completedLines;
    p->alive = alive;

    data = reinterpret_cast<char *>(p);

    return sizeof(player);
}

void Player::deserialize(int size, char* data)
{
    auto* p = reinterpret_cast<player *>(data);

    name = p->name;
    level = p->level;
    score = p->score;
    completedLines = p->completedLines;
    alive = p->alive;

}

messageType Player::getType() {
    return PLAYER_DATA;
}

void Player::setName(char* n) {
    name = n;
}



