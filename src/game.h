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
    std::vector<std::vector<int>> matrix; // Matrix of the game 20*10
    Tetromino current_tetromino;
    Tetromino next_tetromino;
    std::uniform_int_distribution<> distrib;

    // Constructor
    Game(std::uniform_int_distribution<> distrib_init) : distrib(distrib_init) {}

    // Destructor
    ~Game() {}



};