#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include "tetromino.h"
#include <algorithm>

// Matrix of tetromino_type, maybe do a template out of it
template <class T>
class Matrix {

  public:

    unsigned int rows;
    unsigned int cols;

    Matrix(const unsigned int rows_init, const unsigned int cols_init) :
        rows(rows_init),
        cols(cols_init),
        data(std::make_unique<T[]>(rows_init*cols_init)) {}

    // Copy constructor
    Matrix(const Matrix &SrcMatrix)
    {
      rows = SrcMatrix.rows;
      cols = SrcMatrix.cols;
      data = std::make_unique<T[]>(rows * cols);
      std::copy_n(SrcMatrix.data.get(), SrcMatrix.rows*SrcMatrix.cols, data.get());
    };

    // TO DO : add move constructor

    ~Matrix() {}

    void Print() {
      for (unsigned int i=0; i<this->rows; i++)
      {
        for (unsigned int j=0; j<this->cols; j++)
        {
          std::cout << this->data[i*(this->cols)+j] << " ";
          
        }
        std::cout << std::endl;
      }
    }

    void Print(const int row, const int col) const {
      std::cout << this->data[row*(this->cols)+col] << std::endl;
    }

    T At(const int row, const int col) const {
      return this->data[row*(this->cols)+col];
    }

    T* At_ptr(const int row, const int col) {
      return &(this->data[row*(this->cols)+col]);
    }

    void To(const int row, const int col, const T value) {
      data[row * cols + col] = value;
    }

    unsigned int GetNumRows() const {
      return rows;
    }

    unsigned int GetNumColumns() const {
      return cols;
    }

protected:

    std::unique_ptr<T[]> data;

};