//
// Created by seb on 28/02/23.
//

#include "disconnect.h"

Disconnect::Disconnect(std::string reason) : reason(reason)
{}


messageType Disconnect::getType() {
    return DISCONNECT;
}

void Disconnect::serialize(std::vector<char> &data) {
    data.resize(SIZE_OF_MESSAGE_SIZE + 1 + (reason.size() + 1));

    for (int i = 0; i < reason.size(); i++)
        data[i + SIZE_OF_MESSAGE_SIZE + 1] = reason[i];

    data[reason.size() + SIZE_OF_MESSAGE_SIZE + 1] = '\0';
}

void Disconnect::deserialize(std::vector<char> data)
{
    char* name = data.data();
    reason = name;
}
