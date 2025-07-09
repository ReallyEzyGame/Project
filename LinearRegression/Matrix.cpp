#include "Matrix.h"



// Constructor & Destructor -----------------------
Matrix::Matrix(int _num_rows, int _num_columns) : num_rows(_num_rows), num_columns(_num_columns)
{
    if (_num_rows <= 0 || _num_columns <= 0)
    {
        pMatrix = nullptr;
        return;
    }
    pMatrix = new double *[num_rows];
    for (int r = 0; r < num_rows; ++r)
    {
        pMatrix[r] = new double[num_columns];
        for (int c = 0; c < num_columns; ++c)
            pMatrix[r][c] = 0;
    }
}
Matrix::Matrix() : num_rows(0), num_columns(0), pMatrix(nullptr) {}
Matrix::Matrix(const vector<double> list) {
    num_rows = list.size();
    num_columns = 1;
    pMatrix = new double*[num_rows];
    for (int i  = 0; i <  list.size(); ++i) {
        pMatrix[i] = new double(list[i]);
    }
}
Matrix::Matrix(const vector<vector<double>> list)
{
    num_rows = list.size();
    num_columns = list[0].size();
    pMatrix = new double *[num_rows];

    for (int r = 0; r < num_rows; ++r)
    {
        pMatrix[r] = new double[num_columns];
        for (int c = 0; c < num_columns; ++c)
            pMatrix[r][c] = list[r][c];
    }
}
Matrix::Matrix(const Matrix &src): num_rows(src.num_rows), num_columns(src.num_columns)
{
    if  (num_rows <= 0 || num_rows <=  0) {
        pMatrix = nullptr;
        return;
    }

    pMatrix = new double *[num_rows];
    for (int r = 0; r < num_rows; ++r)
    {
        pMatrix[r] = new double[num_columns];
        for (int c = 0; c < num_columns; ++c)
            pMatrix[r][c] = src.pMatrix[r][c];
    }
}
Matrix::Matrix(Matrix&& src) noexcept :
    num_rows(src.num_rows), num_columns(src.num_columns), pMatrix(src.pMatrix)
{
    src.num_rows = src.num_columns = 0;
    src.pMatrix = nullptr;              // Avoid Delete Again
}
Matrix::~Matrix()
{
    if (pMatrix == nullptr) return;

    for (int r = num_rows - 1; r >= 0; --r)
    {
        delete[] pMatrix[r];
        pMatrix[r];
    }
    delete[] pMatrix;
    pMatrix = nullptr;
    num_rows = num_columns =  0;
}





// Operator ---------------------------------------
const Matrix Matrix::operator+(const Matrix &Mat) const
{
    // Invalid Matrix  Size
    if (num_rows != Mat.num_rows || num_columns != Mat.num_columns)
        return Matrix(0, 0);

    Matrix addMat(num_rows, num_columns);
    for (int r = 0; r < num_rows; ++r)
        for (int c = 0; c < num_columns; ++c)
            addMat.pMatrix[r][c] = pMatrix[r][c] + Mat.pMatrix[r][c];
    return addMat;
}
const Matrix Matrix::operator-(const Matrix &Mat) const
{
    // Invalid Matrix Size
    if (num_rows != Mat.num_rows || num_columns != Mat.num_columns)
        return Matrix(0, 0);

    Matrix minMat(num_rows, num_columns);
    for (int r = 0; r < num_rows; ++r)
        for (int c = 0; c < num_columns; ++c)
            minMat.pMatrix[r][c] = pMatrix[r][c] - Mat.pMatrix[r][c];
    return minMat;
}
const Matrix Matrix::operator*(const Matrix &Mat) const
{
    if (num_columns != Mat.num_rows) // Invalid Matrix Size
        return Matrix(0, 0);

    Matrix mulMat(num_rows, Mat.num_columns);
    for (int r = 0; r < num_rows; ++r)
    {
        for (int c_res = 0; c_res < Mat.num_columns; ++c_res)
        {
            double total = 0;
            for (int k = 0; k < num_columns; ++k)
            {
                total += pMatrix[r][k] * Mat.pMatrix[k][c_res];
            }
            mulMat.pMatrix[r][c_res] = total;
        }
    }
    return mulMat;
}
const Matrix Matrix::operator*(double k) const
{
    Matrix mulMat(*this);

    for (int r = 0; r < num_rows; ++r)
    {
        for (int c = 0; c < num_columns; ++c)
            mulMat.pMatrix[r][c] *= k;
    }
    return mulMat;
}
Matrix operator*(double k, const Matrix &Mat)
{
    Matrix mulMat(Mat);

    for (int r = 0; r < Mat.num_rows; ++r)
    {
        for (int c = 0; c < Mat.num_columns; ++c)
            mulMat.pMatrix[r][c] *= k;
    }
    return mulMat;
}
Matrix& Matrix::operator=(const Matrix& src)
{
    if (this == &src) return *this;         // Avoid Copy itself
    // Release the Memory
    if (pMatrix != nullptr) {
        for (int i = 0; i < num_rows;++i) 
            delete[] pMatrix[i];
        delete[] pMatrix;
    }

    num_rows = src.num_rows;
    num_columns =  src.num_columns;
    pMatrix =  src.pMatrix;
    // Empty Matrix
    if (num_rows <= 0 || num_columns <= 0) {
        pMatrix = nullptr;
        return *this;
    }
    pMatrix = new double*[num_rows];
    for (int r = 0; r  <num_rows; ++r) {
        pMatrix[r] =   new double[num_columns];
        for (int c = 0; c < num_columns; ++c)
            pMatrix[r][c] = src.pMatrix[r][c];
    }
    return *this;
}
double *Matrix::operator[](const int idx) const
{
    if (idx < 0 || num_rows <= idx)
        return nullptr;
    return pMatrix[idx];
}
double Matrix::operator()(const int r, const int c) const
{
    if (r < 0 || num_rows <= r || c < 0 || num_columns <= c)
        return -1;
    return pMatrix[r][c];
}



// Extract Information --------------------------
int Matrix::row() const { return num_rows; }
int Matrix::column() const { return num_columns; }
ostream &operator<<(ostream &out, const Matrix &matrix)
{
    for (int r = 0; r < matrix.row(); ++r)
    {
        for (int c = 0; c < matrix.column(); ++c)
            out << matrix.pMatrix[r][c] << " ";
        out << endl;
    }
    return out;
}
double Matrix::determinant()
{
    double det = 1;
    bool change = false;
    Matrix Mat = this->GaussElimination(change);
    Matrix cut = Mat;
    do
    {
        det *= cut[0][0];
        cut = cut.subMatrix(0, 0);
    } while (cut.row() >= 1 && cut.column() >= 1);
    return change ? -1.0 * det : 1.0 * det;
}
int Matrix::rank()
{
    Matrix stairMat = this->GaussElimination();
    return num_rows - stairMat.countLineZero();
}
Matrix Matrix::subMatrix(const int ExcludeRow, const int ExcludeColumn)
{
    // Invalid Row/Column
    if (ExcludeRow < 0 || ExcludeColumn < 0 || num_rows <= ExcludeRow || num_columns <= ExcludeColumn)
        return *this;

    Matrix Mat(num_rows - 1, num_columns - 1);
    int r = 0, oldRow = 0;
    while (oldRow < num_rows)
    {
        if (oldRow == ExcludeRow)
        {
            oldRow++;
            continue;
        }

        int c = 0, oldColumn = 0;
        while (oldColumn < num_columns)
        {
            if (oldColumn == ExcludeColumn)
            {
                oldColumn++;
                continue;
            }
            Mat[r][c++] = pMatrix[oldRow][oldColumn++];
        }
        r++; oldRow++;
    }
    return Mat;
}
Matrix Matrix::excludeRow(const int ExcludeRow) {
    Matrix excMat(num_rows - 1,num_columns);
    if (excMat.num_rows < 0) return Matrix(0,0);

    int row = 0, column = 0;
    for (int r = 0; r  < num_rows; ++r) {
        if  (row ==  ExcludeRow) continue;

        for (int  c = 0; c < num_columns; ++c) {
            this->pMatrix[r][c] = excMat.pMatrix[r][c];
        }
    }
    return excMat;
}



// Matrix Manipulator ----------------------------
// Return the  Stair Matrix
Matrix Matrix::GaussElimination()
{
    Matrix gaussMat(*this);

    for (int r = 0, col = 0; r < gaussMat.num_rows && col < gaussMat.num_columns; ++r, ++col)
    {
        // find the Pivot
        int pivot = r;
        while (pivot < num_rows && gaussMat[pivot][col] == 0)
            pivot++;
        if (pivot >= num_rows)
            continue; // Column of 0

        swap(gaussMat.pMatrix[r], gaussMat.pMatrix[pivot]);
        // Elimination
        for (int r1 = r + 1; r1 < num_rows; ++r1)
        {
            double base = 1.0 * gaussMat.pMatrix[r1][col] / gaussMat.pMatrix[r][col];

            for (int c1 = col; c1 < num_columns; ++c1)
            {
                double tmp = gaussMat.pMatrix[r1][c1] - gaussMat.pMatrix[r][c1] * base;
                if (abs(tmp) <= pow(10,-6)) tmp =  0;
                gaussMat.pMatrix[r1][c1] = tmp;
            }
        }
    }
    return gaussMat;
}
// Return the 'rut gon' Stair Matrix
Matrix Matrix::GaussJordanElimination()  {
    // Gauss Elimination
    Matrix gaussMat = this->GaussElimination();
    // Gauss-Jordan Elimination
    for (int r = gaussMat.num_rows - 1;; --r) {
        if (rowOfZero(r)) continue;     // Ignore the Row of Zero

        // find the base
        int pivot = 0;
        while (gaussMat[r][pivot] == 0) pivot++;


        double base =  gaussMat[r][pivot];
        // Simplize the current Row
        for (int c =  0; c < num_columns; ++c)
            gaussMat[r][c] /= base;


        // Elimination other Rows
        if (r == 0) break;
        for (int r1 = r - 1; r1 >= 0; --r1) {
            base = 1.0 * gaussMat[r1][pivot] / gaussMat[r][pivot];
            for (int c1 = pivot; c1 < num_columns; ++c1) {
                double tmp = gaussMat.pMatrix[r1][c1] - gaussMat.pMatrix[r][c1] * base;
                if (abs(tmp) <= pow(10,-6)) tmp =  0;
                gaussMat.pMatrix[r1][c1] = tmp;
            }
        }
    }
    return gaussMat;
}
// Return the  Inverse Matrix
Matrix Matrix::inverse() {
    if (this->determinant() == 0) return Matrix(0,0);   // UnInversable

    Matrix expMat(this->num_rows, 2*this->num_columns);     // Expand Matrix
    // Initialize the input matrix on the left
    for (int r = 0; r < num_rows; ++r)
        for (int c =  0; c < num_columns; ++c)
            expMat[r][c] = this->pMatrix[r][c];
    // Initialize the Identity matrix on the right
    for (int d = 0; d < num_rows; ++d)
        expMat[d][num_columns + d] = 1;

    expMat =  expMat.GaussJordanElimination();

    Matrix invMat(num_rows, num_columns);
    for (int r = 0; r < num_rows; ++r) {
        for (int c = 0; c < num_columns; ++c)
            invMat[r][c] = expMat[r][num_columns + c];
    }
    return invMat;
}
// the Specialized Gauss Elimination using toNegative boolean to decides
// if the determinant of the matrix to change the sign
Matrix Matrix::GaussElimination(bool &toNegative)
{
    Matrix gaussMat(*this);

    for (int r = 0, col = 0; r < gaussMat.num_rows && col < gaussMat.num_columns; ++r, ++col)
    {
        // find the Pivot
        int pivot = r;
        while (pivot < num_rows && gaussMat[pivot][col] == 0)
            pivot++;
        if (pivot >= num_rows)
            continue; // Column of 0
        toNegative = pivot == r ? toNegative : !toNegative;

        swap(gaussMat.pMatrix[r], gaussMat.pMatrix[pivot]);
        // Elimination
        for (int r1 = r + 1; r1 < num_rows; ++r1)
        {
            double base = 1.0 * gaussMat.pMatrix[r1][col] / gaussMat.pMatrix[r][col];

            for (int c1 = col; c1 < num_columns; ++c1)
            {
                double tmp = gaussMat.pMatrix[r1][c1] - gaussMat.pMatrix[r][c1] * base;
                if (abs(tmp) <= pow(10,-6)) tmp =  0;
                gaussMat.pMatrix[r1][c1] = tmp;
            }
        }
    }
    return gaussMat;
}
int Matrix::countLineZero()
{
    int cnt = 0;
    for (int r = 0; r < num_rows; ++r)
    {
        int c = 0;
        for (; c < num_columns; ++c)
            if (pMatrix[r][c]) break; // Found a valaue not 0

        if (c == num_columns) ++cnt;
    }
    return cnt;
}
Matrix Matrix::Transpose() {
    Matrix tranMat(this->column(), this->row());

    for (int r = 0; r < num_rows; ++r) {
        for (int c = 0;  c < num_columns; ++c)
            tranMat[c][r] = this->pMatrix[r][c];
    }
    return tranMat;
}



// Return the Identity Matrix with the size of n
Matrix Identity(int n) {
    if (n <= 0) return Matrix(0,0);

    Matrix Mat(n,n);
    for (int d = 0; d < n; ++d)
        Mat[d][d] = 1;
    return Mat;
}




// Support Function
bool Matrix::rowOfZero(const int row) {
    if (row < 0 || num_rows <= row) return false;
    for (int c = 0; c < num_columns; ++c)
        if  (pMatrix[row][c]) return false;     // found the  value not 0
    return true;
}