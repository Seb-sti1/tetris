//
// Created by seb on 19/02/23.
//

#include "messageable.h"

struct data {
    char size[SIZE_OF_MESSAGE_SIZE];
    char type;
    char* content;
};


char* messageable::toData() {
    data* toSend = new data;

    for (char & c : toSend->size)
        c = '0';

    int size = SIZE_OF_MESSAGE_SIZE + 1 + serialize(toSend->content);

    for (int i = 0; i < SIZE_OF_MESSAGE_SIZE; i++)
    {

    }

    toSend->type = type;



    return (char*) toSend;

}