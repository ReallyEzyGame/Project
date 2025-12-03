#include <iostream>

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


bool is_symmetric(const Matrix& matrix) {
  if (matrix.n_cols != matrix.n_rows) {
    return false;
  }


  for (int i = 0; i < matrix.n_rows; ++i) {
    for (int j = i + 1; j < matrix.n_cols; ++j) {
      if (matrix.data[i][j] != matrix.data[j][i]) {
        return false;
      }
    }
  }

  return true;
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
  int N, M, k;
  Matrix matrix;

  std::cout << "Input  size N,M and rotate k: ";
  std::cin >> N >> M >> k;

  matrix = create_matrix(N, M);


  for (int r = 0; r < matrix.n_rows; ++r)
  {
    for (int c = 0; c < matrix.n_cols; ++c)
    {
      std::cout << matrix.data[r][c] << " ";
    }
    std::cout << std::endl;
  }
  if (is_symmetric(matrix)) {
    std::cout << "is a Symmetric Matrix\n";
  }

  destroy_matrix(matrix);
}