#pragma once

#include "matrix.h"

enum tetromino_type {I, O, T, L, J, Z, S};
enum orient {UP, RIGHT, DOWN, LEFT};

int tetromino_rows = 4;
int tetromino_cols = 3;

Matrix<bool> I_matrix(tetromino_rows, tetromino_cols);
for(int i=0; i<tetromino_rows; i++) I_matrix.To(i,1,true);

Matrix<bool> O_matrix(tetromino_rows, tetromino_cols);
O_matrix.To(0,0,true);
O_matrix.To(0,1,true);
O_matrix.To(1,0,true);
O_matrix.To(1,1,true);

Matrix<bool> T_matrix(tetromino_rows, tetromino_cols);
T_matrix.To(0,0,true);
T_matrix.To(0,1,true);
T_matrix.To(0,2,true);
T_matrix.To(1,1,true);

Matrix<bool> L_matrix(tetromino_rows, tetromino_cols);
L_matrix.To(0,0,true);
L_matrix.To(1,0,true);
L_matrix.To(2,0,true);
L_matrix.To(2,1,true);

Matrix<bool> J_matrix(tetromino_rows, tetromino_cols);
J_matrix.To(0,1,true);
J_matrix.To(1,1,true);
J_matrix.To(2,1,true);
J_matrix.To(2,0,true);

Matrix<bool> Z_matrix(tetromino_rows, tetromino_cols);
Z_matrix.To(0,0,true);
Z_matrix.To(0,1,true);
Z_matrix.To(1,1,true);
Z_matrix.To(1,2,true);

Matrix<bool> S_matrix(tetromino_rows, tetromino_cols);
S_matrix.To(0,1,true);
S_matrix.To(0,2,true);
S_matrix.To(1,0,true);
S_matrix.To(1,1,true);

class Tetromino {

    public:

        tetromino_type type;
        unsigned int x;
        unsigned int y;
        orient orientation;

        bool verify_move_validity(std::vector<std::vector<int>> matrix, orient orientation)
        {

        }

};