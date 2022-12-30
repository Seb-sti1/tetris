#pragma once

#include <ctime>
#include "tetromino.h"
#include <vector>

class Game {
public:
    time_t start_date;
    unsigned int score;
    unsigned int completed_lines;
    std::vector<std::vector<int>> matrix;
    Tetromino next_tetromino;

};