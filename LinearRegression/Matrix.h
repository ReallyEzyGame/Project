#include "lib.h"

#ifndef _MATRIX_H
#define _MATRIX_H

// Using for th
class Matrix
{
private:
    double **pMatrix;
    int num_rows, num_columns;

public:
    // Constructor & Destructor ----------------------
    Matrix(int, int);
    Matrix();
    Matrix(const vector<double>);
    Matrix(const vector<vector<double>>);
    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;
    ~Matrix();

    // Matrix Manipulate ----------------------------
    const Matrix operator+(const Matrix &) const;
    const Matrix operator-(const Matrix &) const;
    const Matrix operator*(const Matrix &) const;
    const Matrix operator*(double) const;
    Matrix& operator=(const Matrix& );
    friend Matrix operator*(double, const Matrix &);

    double *operator[](const int) const;
    double operator()(const int, const int) const;

    Matrix GaussElimination();
    Matrix GaussElimination(bool&);
    Matrix GaussJordanElimination();
    Matrix inverse();

    // Extract Information --------------------
    int row() const;
    int column() const;
    double determinant();
    int rank();
    bool rowOfZero(const int);
    Matrix subMatrix(const int, const int);
    Matrix excludeRow(const int row);



    // Matrix Tranformation --------------------------
    Matrix Diagonalization();
    Matrix Transpose();
// Function to  support other  function
private:
    int countLineZero();
public:
    // Matrix's Friend -------------------------------
    friend ostream &operator<<(ostream &, const Matrix &);
};


Matrix Identity(int n);
#endif