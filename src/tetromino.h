#pragma once

#include "matrix.h"

#define TETROMINO_ROWS 4
#define TETROMINO_COLS 4


enum tetromino_type {NONE = 0, I, O, T, L, J, Z, S};
enum orient {UP, RIGHT, DOWN, LEFT};


class Tetromino {

    public:

        tetromino_type type;
        unsigned int x;
        unsigned int y;
        orient orientation;

        Tetromino(Tetromino const &t) : type(t.type),
                                 x(t.x),
                                 y(t.y),
                                 orientation(t.orientation) {}


        Tetromino(tetromino_type type_init) :
        type(type_init),
        x(0),
        y(0) {}

        Tetromino(tetromino_type type_init, unsigned int x_init, unsigned int y_init) :
        type(type_init),
        x(x_init),
        y(y_init) {}

        Tetromino(tetromino_type type_init, unsigned int x_init, unsigned int y_init, orient orientation_init) :
        type(type_init),
        x(x_init),
        y(y_init),
        orientation(orientation_init) {}

        ~Tetromino() = default;

        bool verify_move_validity(Matrix<tetromino_type>& matrix) const
        {
            Matrix<bool> collision_matrix = this->get_collision_matrix();
            for(unsigned int i = 0; i < TETROMINO_COLS; i++)
            {
                for(unsigned int j = 0; j < TETROMINO_ROWS; j++)
                {
                    if ((matrix.At(this->x+i, this->y+j)!=NONE)
                    && collision_matrix.At(i, j))
                    {
                        return false;
                    }
                }
            }
            return true; // the move is considered valid
        }

        
        Matrix<bool> get_collision_matrix() const
        {
            Matrix<bool> tetro_matrix(TETROMINO_ROWS, TETROMINO_COLS);
            switch (this->type)
            {
                case I:
                    for(int i=0; i<TETROMINO_ROWS; i++) tetro_matrix.To(i,1,true);
                    break;
                case O:
                    tetro_matrix.To(0,0,true);
                    tetro_matrix.To(0,1,true);
                    tetro_matrix.To(1,0,true);
                    tetro_matrix.To(1,1,true);
                    break;
                case T:
                    tetro_matrix.To(0,0,true);
                    tetro_matrix.To(0,1,true);
                    tetro_matrix.To(0,2,true);
                    tetro_matrix.To(1,1,true);
                    break;
                case L:
                    tetro_matrix.To(0,0,true);
                    tetro_matrix.To(1,0,true);
                    tetro_matrix.To(2,0,true);
                    tetro_matrix.To(2,1,true);
                    break;
                case J:
                    tetro_matrix.To(0,1,true);
                    tetro_matrix.To(1,1,true);
                    tetro_matrix.To(2,1,true);
                    tetro_matrix.To(2,0,true);
                    break;
                case Z:
                    tetro_matrix.To(0,0,true);
                    tetro_matrix.To(0,1,true);
                    tetro_matrix.To(1,1,true);
                    tetro_matrix.To(1,2,true);
                    break;
                case S:
                    tetro_matrix.To(0,1,true);
                    tetro_matrix.To(0,2,true);
                    tetro_matrix.To(1,0,true);
                    tetro_matrix.To(1,1,true);
                    break;
                default:
                    std::cout << "Enter a correct tetromino_type" << std::endl;
            }
            return tetro_matrix;
        }

};