#pragma once
#include <time.h>
#include <vector.h>
#include <tetromino.h>
#include <matrix.h>

class Game {

    public:

        time_t start_date;
        unsigned int score;
        unsigned int completed_lines;
        std::vector<std::vector<int>> matrix;
        tetromino next_tetromino;


}