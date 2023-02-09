#pragma once

#include <iostream>
#include <cstdlib>
#include <memory>
#include "tetromino.h"
#include <algorithm>

// Matrix of tetromino_type, maybe do a template out of it
template<class T>
class Matrix {

public:

    unsigned int rows;
    unsigned int cols;

    Matrix(const unsigned int rows_init, const unsigned int cols_init) :
            rows(rows_init),
            cols(cols_init),
            data(std::make_unique<T[]>(rows_init * cols_init)) {}

    // Copy constructor
    Matrix(const Matrix<T> &SrcMatrix) {
        rows = SrcMatrix.rows;
        cols = SrcMatrix.cols;
        data = std::make_unique<T[]>(rows * cols);
        std::copy_n(SrcMatrix.data.get(), SrcMatrix.rows * SrcMatrix.cols, data.get());
    }

    ~Matrix() {}

    void Print() {
        for (unsigned int i = 0; i < this->rows; i++) {
            for (unsigned int j = 0; j < this->cols; j++) {
                std::cout << this->data[i * (this->cols) + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "---" << std::endl;
    }

    void Print(const int row, const int col) const {
        std::cout << this->data[row * (this->cols) + col] << std::endl;
    }

    //Same type matrixes addition
    //TODO fix it
    Matrix<T> operator+(Matrix<T> B_matrix) {
        if ((this->rows != B_matrix.GetNumRows()) || (this->cols != B_matrix.GetNumColumns())) {
            //TODO exception si pas les mêmes tailles
            std::cout << "Matrixes are different sizes : Addition aborted" << std::endl;
            return *this;
        } else {
            Matrix<T> res_matrix(this->rows, this->cols);
            for (unsigned int i = 0; i < this->cols; i++) {
                for (unsigned int j = 0; j < this->rows; j++) {
                    res_matrix.To(i, j, this->At(i, j) + B_matrix.At(i, j));
                }
            }
            return res_matrix;
        }
    }

    T At(const int row, const int col) const {
        return this->data[row * (this->cols) + col];
    }

    T *At_ptr(const int row, const int col) {
        return &(this->data[row * (this->cols) + col]);
    }

    void To(const int row, const int col, const T value) {
        data[row * (this->cols) + col] = value;
    }

    unsigned int getNumRows() const {
        return rows;
    }

    unsigned int getNumColumns() const {
        return cols;
    }

    //Only for square matrixes now
    //TODO finish rotateLeft
    void rotateLeft(int px, int py) {
        auto copy(*this);

        for (unsigned int i = 0; i < getNumRows(); i++) {
            for (unsigned int j = 0; j < getNumColumns(); j++) {
                unsigned x = (j - px + py) % getNumRows();
                unsigned y = (getNumColumns() - 1 - i - px - py) % getNumColumns();

                To(i, j, copy.At(x, y));
            }
        }
    }


protected:

    std::unique_ptr<T[]> data;

};