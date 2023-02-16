#pragma once

#include "matrix.h"

#define TETROMINO_ROWS 3
#define TETROMINO_COLS 3


enum tetromino_type {
    NONE = 0, I, O, T, L, J, Z, S
};
enum orient {
    UP, LEFT, DOWN, RIGHT
};


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

    bool verify_move_validity(Matrix<tetromino_type> &matrix) const {
        Matrix<bool> collision_matrix = this->get_collision_matrix();
        for (unsigned int i = 0; i < collision_matrix.getNumRows(); i++) {
            for (unsigned int j = 0; j < collision_matrix.getNumColumns(); j++) {

                // if there is a part of the tetromino in i, j
                // and either the corresponding cell is already occupy or outside the matrix
                // then return false
                if (collision_matrix.At(i, j) &&
                    (x + i >= matrix.getNumRows()
                     || y + j >= matrix.getNumColumns()
                     || matrix.At(x + i, y + j) != NONE)) {
                    return false;
                }
            }
        }
        return true; // the move is considered valid
    }


    Matrix<bool> get_collision_matrix() const {
        // initialize a 3x3 matrix for every type but the I type that requires 4x4 matrix
        Matrix<bool> tetro_matrix(TETROMINO_ROWS+(this->type==I), TETROMINO_COLS+(this->type==I));

        switch (this->type) {
            case I:
                for (int i = 0; i < TETROMINO_ROWS+1; i++) tetro_matrix.To(i, 1, true);
                break;
            case O:
                tetro_matrix.To(0, 0, true);
                tetro_matrix.To(0, 1, true);
                tetro_matrix.To(1, 0, true);
                tetro_matrix.To(1, 1, true);
                break;
            case T:
                tetro_matrix.To(0, 0, true);
                tetro_matrix.To(0, 1, true);
                tetro_matrix.To(0, 2, true);
                tetro_matrix.To(1, 1, true);
                break;
            case L:
                tetro_matrix.To(0, 1, true);
                tetro_matrix.To(1, 1, true);
                tetro_matrix.To(2, 1, true);
                tetro_matrix.To(2, 2, true);
                break;
            case J:
                tetro_matrix.To(0, 1, true);
                tetro_matrix.To(1, 1, true);
                tetro_matrix.To(2, 1, true);
                tetro_matrix.To(2, 0, true);
                break;
            case Z:
                tetro_matrix.To(1, 2, true);
                tetro_matrix.To(1, 1, true);
                tetro_matrix.To(2, 0, true);
                tetro_matrix.To(2, 1, true);
                break;
            case S:
                tetro_matrix.To(2, 2, true);
                tetro_matrix.To(1, 1, true);
                tetro_matrix.To(1, 0, true);
                tetro_matrix.To(2, 1, true);
                break;
            default:
                std::cout << "Enter a correct tetromino_type" << std::endl;
        }

        if (this->type!=O) // O does not need to rotate and it would create wrong moves because it is not centered in the collision matrix
        {
            switch (orientation) {
                case RIGHT:
                    tetro_matrix.rotateRight();
                    break;
                case DOWN:
                    tetro_matrix.rotateLeft();
                    tetro_matrix.rotateLeft();
                    break;
                case LEFT:
                    tetro_matrix.rotateLeft();
                    break;
            }
        }

        return tetro_matrix;
    }

    int getSpawningX()
    {
        auto collision = get_collision_matrix();

        for (int i = 0; i < collision.getNumRows(); i++) {
            for (int j = 0; j < collision.getNumColumns(); j++) {
                if (collision.At(i, j))
                    return i;
            }
        }

        return -1;
    }


    void print()
    {
        Matrix<bool> collision_matrix = this->get_collision_matrix();
        for (unsigned int i = 0; i < collision_matrix.getNumColumns(); i++) {
            for (unsigned int j = 0; j < collision_matrix.getNumRows(); j++) {
                std::cout << (collision_matrix.At(i, j) ? "x" : "_");
            }
            std::cout << std::endl;
        }
    }

};