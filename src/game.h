#pragma once

#include <ctime>
#include "tetromino.h"
#include <vector>
#include <random>

enum GameState {WAITING, IN_GAME};

class Game {

public:
    // Attributes
    Matrix<tetromino_type> matrix; // Matrix of the game 20*10

    // Constructor
    Game();
    // Destructor
    //~Game();

    void StartGame(long seed);


private:
    GameState state;

    time_t start_date;
    unsigned int score;
    unsigned int completed_lines;

    Tetromino current_tetromino;
    Tetromino next_tetromino;

    std::uniform_int_distribution<> distrib;
    std::mt19937 gen;


};