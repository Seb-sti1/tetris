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


char* messageable::toData() {
    data* toSend = new data;

    int size = SIZE_OF_MESSAGE_SIZE + 1 + serialize(toSend->content);

    for (int i = 0; i < SIZE_OF_MESSAGE_SIZE; i++)
    {
        int c = size/pow(10, SIZE_OF_MESSAGE_SIZE - i);
        toSend->size[i] = c + '0';

        size -= c*pow(10, SIZE_OF_MESSAGE_SIZE - i);
    }

    toSend->type = getType();

    return (char*) toSend;
}

messageType messageable::getType() {
    return UNKNOWN;
}
