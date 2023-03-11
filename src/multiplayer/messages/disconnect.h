//
// Created by seb & billy on 28/02/23.
//

#ifndef TETRIS_DISCONNECT_H
#define TETRIS_DISCONNECT_H

#include <string>
#include "messageable.h"

class Disconnect : public Messageable {

public:
    Disconnect(std::string reason);
    Disconnect() = default;

    /**
     * The reason of deconnection
     */
    std::string reason;

    void serialize(std::vector<char> &data) override;
    void deserialize(std::vector<char> data) override;
    messageType getType() override;

};


#endif //TETRIS_DISCONNECT_H
