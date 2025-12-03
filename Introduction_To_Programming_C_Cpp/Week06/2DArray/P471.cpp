#include <iostream>
#include <exception>

struct Matrix
{
  float **data;
  int n_rows, n_cols;
};

Matrix create_matrix(const int n_rows, const int n_cols)
{
  float **matrix = new float *[n_rows];

  std::cout << "Input Matrix values: ";
  for (int i = 0; i < n_rows; ++i)
  {
    matrix[i] = new float[n_cols];

    for (int j = 0; j < n_cols; ++j)
    {
      int num;

      std::cin >> num;
      matrix[i][j] = num;
    }
  }
  return {matrix, n_rows, n_cols};
}
void destroy_matrix(Matrix &matrix)
{

  for (int r = 0; r < matrix.n_rows; ++r)
  {
    delete[] matrix.data[r];
  }

  delete[] matrix.data;
  matrix.data = nullptr;
  matrix.n_rows = matrix.n_cols = 0;
}


Matrix product(const Matrix& mat1, const Matrix& mat2) {
  if (mat1.n_cols != mat2.n_rows) {
    //throw std::exception("Error: Invalid Matrix Size");
  }

  int rows = mat1.n_rows;
  int cols = mat2.n_cols;
  int len = mat1.n_cols;
  float** mat_prod = new float*[mat1.n_rows];

  for  (int i = 0; i < mat1.n_rows; ++i) {
    mat_prod[i] = new float[mat2.n_cols];
  }

  for (int r = 0; r < rows; ++r) {
    float total = 0;
    for (int c = 0; c < cols; ++c) {
      for (int i = 0; i < len; ++i) {
        total += mat1.data[r][c + i] * mat2.data[r + i][c];
      }
    }
  }

  return  Matrix{mat_prod, rows, cols};;
}


// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input:
// Output:

// Test case 2
// Input:
// Output:

// Test case 3
// Input:
// Output:
int main()
{
  int N, M, P;
  Matrix matrix1;
  Matrix matrix2;
  std::cout << "Input  size N,M, P of 2 matrix: ";
  std::cin >> N >> M >> P;

  matrix1 = create_matrix(N, M);
  matrix2 = create_matrix(M, P);


  std::cout <<  "Product of  Matrix 1 & Matrix 2 is";
  Matrix prod_matrix = product(matrix1, matrix2);
  for (int r = 0; r < prod_matrix.n_rows; ++r) {
    for (int c = 0; c < prod_matrix.n_cols; ++c) {
      std::cout << prod_matrix.data[r][c] <<  " ";
    }
    std::cout << std::endl;
  }

  destroy_matrix(matrix1);
  destroy_matrix(matrix2);
}