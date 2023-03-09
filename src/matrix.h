#pragma once

#include <iostream>
#include <cstdlib>
#include <memory>
#include <algorithm>


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

    T At(const int row, const int col) const {
        return this->data[row * (this->cols) + col];
    }

    T *At_ptr(const int row, const int col) {
        return &(this->data[row * (this->cols) + col]);
    }

    void resetToValue(const T value)
    {
        for (int i = 0; i < getNumRows(); i++) {
            for (int j = 0; j < getNumColumns(); j++) {
                To(i, j, value);
            }
        }
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

    // only for square matrixes
    void rotateLeft() {
        if (this->cols==this->rows)
        {
            for (unsigned int i = 0; i < this->rows/2; i++)
            {
                for (unsigned int j = i; j < this->cols-i-1; j++)
                {
                    int temp=this->At(i,j);
                    this->To(i,j,this->At(j, this->rows-i-1));
                    this->To(j,this->rows-i-1,this->At(this->rows-i-1,this->rows-j-1));
                    this->To(this->rows-i-1,this->rows-j-1,this->At(this->rows-j-1,i));
                    this->To(this->rows-j-1,i,temp);
                }
            }
        }
    }

    // only for square matrixes
    void rotateRight() {
        if (this->cols==this->rows)
        {
            for (unsigned int i = 0; i < this->rows/2; i++)
            {
                for (unsigned int j = i; j < this->cols-i-1; j++)
                {
                    int temp=this->At(i,j);
                    this->To(i,j,this->At(this->rows-j-1, i));
                    this->To(this->rows-j-1, i, this->At(this->rows-i-1,this->rows-j-1));
                    this->To(this->rows-i-1,this->rows-j-1,this->At(j, this->rows-i-1));
                    this->To(j, this->rows-i-1,temp);
                }
            }
        }
    }


protected:
    std::unique_ptr<T[]> data;

};