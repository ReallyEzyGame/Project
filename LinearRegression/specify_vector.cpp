#include "specify_vector.h"

// Note: a vector can be  consider as a Matrix has a single Colunm

// return  the basis-vector with the same direction with input vector
vector<double> norm(vector<double> in) {
    double total = 0;
    for (double val:in)
        total += val*val;
    if (total ==  0) return  in;        // Vector 0 case

    double base = sqrt(total);
    for (double& val:in)
        val /= base;
    return in;
} 
int signnum(const double num) {
    if (num == 0) return 0;
    return num > 0 ? 1:-1;
}
Matrix HouseHolderMatrix(const vector<double> u) {
    Matrix mat(u);
    Matrix mulMat   = mat * mat.Transpose();
    Matrix dotPro   = mat.Transpose() * mat;
    double det      = dotPro.determinant();

    return (Identity(mat.row()) - (2.0/det)*mulMat);
}
Matrix HouseHolderMatrix(Matrix mat) {
    Matrix mulMat   = mat * mat.Transpose();
    Matrix dotPro   = mat.Transpose() * mat;
    double det      = dotPro.determinant();

    return (Identity(mat.row()) - (2.0/det)*mulMat);
}
double EuclidLen(const Matrix vec)  {
    double result = 0;
    for (int i = 0; i < vec.row(); ++i)
        result += vec[0][i]*vec[0][i];
    return sqrt(result);
}