//
// Created by seb & billy on 01/03/23.
//

#ifndef TETRIS_GETPLAYERDATA_H
#define TETRIS_GETPLAYERDATA_H


#include "messageable.h"

class GetPlayerData : public Messageable {
public:
    void serialize(std::vector<char> &data) override;
    void deserialize(std::vector<char> data) override;

    messageType getType() override;
};


#endif //TETRIS_GETPLAYERDATA_H
