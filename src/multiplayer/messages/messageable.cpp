//
// Created by seb on 19/02/23.
//

#include <cmath>
#include "messageable.h"

struct data {
    char size[SIZE_OF_MESSAGE_SIZE];
    char type;
    char* content;
};


void Messageable::toData(std::vector<char> &data)
{
    serialize(data);

    int size = data.size();
    for (int i = 0; i < SIZE_OF_MESSAGE_SIZE; i++)
    {
        int c = size/pow(10, SIZE_OF_MESSAGE_SIZE - i - 1);
        data[i] = c + '0';

        size -= c*pow(10, SIZE_OF_MESSAGE_SIZE - i - 1);
    }

    data[4] = getType();
}

messageType Messageable::getType() {
    return UNKNOWN;
}
