#pragma once

#include <ctime>
#include "tetromino.h"
#include <vector>
#include <random>

class Game {

public:

    // Attributes
    time_t start_date;
    unsigned int score;
    unsigned int completed_lines;
    Matrix<tetromino_type> matrix; // Matrix of the game 20*10
    Tetromino current_tetromino;
    Tetromino next_tetromino;
    std::uniform_int_distribution<> distrib;

    // Constructor
    Game(std::uniform_int_distribution<> distrib_init) :
    distrib(distrib_init),
    matrix(20, 10)
    {}

    // Destructor
    ~Game() {}



};