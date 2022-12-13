#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <memory>
#include "tetromino.h"
#include <algorithm>

class Matrix {

  public:

    unsigned int rows;
    unsigned int cols;

    Matrix(const unsigned int rows_init, const unsigned int cols_init) :
        rows(rows_init),
        cols(cols_init),
        data(std::make_unique<tetromino_type[]>(rows_init*cols_init)) {}

    // Copy constructor
    Matrix(const Matrix &SrcMatrix)
    {
      printf("copy\n");
      rows = SrcMatrix.rows;
      cols = SrcMatrix.cols;
      data = std::make_unique<tetromino_type[]>(rows * cols);
      std::copy_n(SrcMatrix.data.get(), SrcMatrix.rows*SrcMatrix.cols, data.get());
      printf("ended\n");

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

private:
    std::unique_ptr<tetromino_type[]> data;

};