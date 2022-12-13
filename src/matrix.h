#pragma once "matrix.h"
#include <iostream>
#include <vector>
#include <memory>
#include "tetromino.h"

class Matrix {

  public:

    unsigned int rows;
    unsigned int cols;
    std::unique_ptr<tetromino_type[]> data;

    Matrix(const int rows_init, const int cols_init): rows{rows_init}, cols{cols_init}, data{std::make_unique<tetromino_type[]>(rows*cols)} {}

    ~Matrix() {}

    void Print() {
      for (int i=1; i<this->rows; i++)
      {
        for (int j=0; j<this->cols; j++)
        {
          std::cout << this->data[i*(this->cols)+j] << std::endl;
        }
      }
    }

    void Print(const int row, const int col) const {
      std::cout << this->data[row*(this->cols)+col] << std::endl;
    }

    int At(const int row, const int col) const {
      return this->data[row*(this->cols)+col];
    }

    //TO DO : add int& At

    int GetNumRows() const {
      return this->rows;
    }

    int GetNumColumns() const {
      return this->cols;
    }
};