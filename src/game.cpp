//
// Created by seb on 01/02/23.
//
#include "game.h"


Game::Game() :
        matrix(20, 10),
        distrib(0, 6),
        score(0),
        completed_lines(0)
{
    state = WAITING;

    // TODO init matrix to a default value ?
    for (int i = 0; i < matrix.GetNumRows(); i++) {
        for (int j = 0; j < matrix.GetNumColumns(); j++) {
            matrix.To(i, j, NONE);
        }
    }
}

void Game::StartGame(long seed) {
    state = IN_GAME;

    gen = std::mt19937(seed);

    start_date = std::time(nullptr);

    current_tetromino.x = 0;
    current_tetromino.y = 0;
    current_tetromino.type = static_cast<tetromino_type>(distrib(gen));
    current_tetromino.orientation = UP;

    next_tetromino.x = 0;
    next_tetromino.y = 0;
    next_tetromino.type = static_cast<tetromino_type>(distrib(gen));
    next_tetromino.orientation = UP;

    // start game loop
}
