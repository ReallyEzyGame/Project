#include "lib.h"
#include "Matrix.h"
#ifndef _SPECIFY_VECTOR_H
#define _SPECIFY_VECTOR_H
/*
    This file has the main purpose is to expand the ability of the already built in <vector> library
    with multiple functions that  includes:
        norm(): find the base-vector of  the   given  vector

*/

vector<double> norm(vector<double>);
int signnum(const double);
Matrix HouseHolderMatrix(const vector<double>);
Matrix HouseHolderMatrix(const Matrix);
double EuclidLen(Matrix);

#endif