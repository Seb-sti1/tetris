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
    explicit Player(int socket);
    /**
     * The socket associated to the client
     */
    int client_socket;

    /**
     * The name
     */
    std::string name = "unknown";

    /**
     * His level
     */
    unsigned level;
    /**
     * His score
     */
    unsigned score;
    /**
     * The number of completed lines
     */
    unsigned completed_lines;
    /**
     * If the player if alive
     */
    bool alive;

    /**
     * If the socket is still connected
     */
    bool connected;

    void serialize(std::vector<char> &data) override;
    void deserialize(std::vector<char> data) override;
    messageType getType() override;

    /**
     * @param n the name of the player
     */
    void setName(std::string n);

    /**
     * Update the player with the game status
     * @param g the game
     */
    void update(Game& g);

    /**
     * Update the player with another player instance
     * @param p the player
     */
    void update(Player* p);
};


#endif //TETRIS_PLAYER_H
