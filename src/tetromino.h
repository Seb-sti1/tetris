#pragma once "tetromino.h"

enum tetromino_type {I, O, T, L, J , Z, S};
enum orient {UP, RIGHT, DOWN, LEFT};



class Tetromino {

    public:

        tetromino_type type;
        unsigned int x;
        unsigned int y;
        orient orientation;

    protected:

        void RotateTetromino()

    

}