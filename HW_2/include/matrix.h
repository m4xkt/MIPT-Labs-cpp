#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<typename T>
class Matrix {
    subvector<T> data;
    unsigned cols_, rows_;

public:
    Matrix(unsigned rows, unsigned cols, int value = 0);
    static Matrix Identity(unsigned dim);
    static Matrix getSpecificDeterminant(unsigned n, T det);

    unsigned rows() const;
    unsigned cols() const;

    Matrix& transpose();
    Matrix transpose() const;

    T& operator()(unsigned row, unsigned col);
    T operator()(unsigned row, unsigned col) const;

    void swaprows_(unsigned i, unsigned j);
    void scale_row(unsigned i, T factor);
    void add_scaled_row(unsigned i, unsigned j, T factor);
};

template<typename T>
T det(const Matrix<T>& mat);
#endif