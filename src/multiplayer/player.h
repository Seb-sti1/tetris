//
// Created by seb on 15/02/23.
//

#ifndef TETRIS_PLAYER_H
#define TETRIS_PLAYER_H


class Player {

public:
    Player(int client_socket);


    char* name;

    unsigned level;
    unsigned score;
    unsigned completedLines;
    bool alive;


private:
    int client_socket;


};


#endif //TETRIS_PLAYER_H
