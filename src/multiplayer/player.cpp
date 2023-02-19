//
// Created by seb on 15/02/23.
//

#include "player.h"

Player::Player(int client_socket)
{
    this->client_socket = client_socket;
}

int Player::serialize(char data)
{



}

void Player::deserialize(char *data)
{




}

messageType Player::getType() {
    return PLAYER_DATA;
}



