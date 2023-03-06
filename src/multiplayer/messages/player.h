//
// Created by seb & billy on 15/02/23.
//

#ifndef TETRIS_PLAYER_H
#define TETRIS_PLAYER_H


#include <string>
#include "messageable.h"
#include "../../game.h"

class Player : public Messageable {

public:
    explicit Player(int &socket);
    int& client_socket;

    std::string name = "unknown";

    unsigned level;
    unsigned score;
    unsigned completed_lines;
    bool alive;

    void serialize(std::vector<char> &data) override;
    void deserialize(std::vector<char> data) override;
    messageType getType() override;

    void setName(char *string);

    void update(Game& g);
    void update(Player* p);
};


#endif //TETRIS_PLAYER_H
