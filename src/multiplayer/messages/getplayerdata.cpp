//
// Created by seb & billy on 01/03/23.
//

#include "getplayerdata.h"


void GetPlayerData::serialize(std::vector<char> &data)
{
    data.resize(SIZE_OF_MESSAGE_SIZE + 1);

    // there no content, the message provide all the useful information
}


void GetPlayerData::deserialize(std::vector<char> data) {}

messageType GetPlayerData::getType()
{
    return GET_PLAYER_DATA;
}
