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

void rotate_border(Matrix &matrix, int k)
{
  int size = 2 * (matrix.n_rows + matrix.n_cols - 2);
  k %= size;
  float *tmp_arr = new float[size];

  int i = 0;
  // Copy Data
  for (int j = 0; j < matrix.n_cols; ++j)
  {
    tmp_arr[i++] = matrix.data[0][j];
  }
  for (int j = 1; j < matrix.n_rows; ++j)
  {
    tmp_arr[i++] = matrix.data[j][matrix.n_cols - 1];
  }
  for (int j = matrix.n_cols - 1; j >= 0; --j)
  {
    tmp_arr[i++] = matrix.data[matrix.n_rows - 1][j];
  }
  for (int j = matrix.n_rows - 2; j >= 0; --j)
  {
    tmp_arr[i++] = matrix.data[0][j];
  }

  i = 0;
  // Shift Data to the new place
  for (int j = 0; j < matrix.n_cols; ++j)
  {
    matrix.data[0][j] = tmp_arr[(i + k) % size];
    i++;
  }
  for (int j = 0; j < matrix.n_rows; ++j)
  {
    matrix.data[j][matrix.n_cols - 1] = tmp_arr[(i + k) % size];
    i++;
  }
  for (int j = matrix.n_cols - 1; j >= 0; --j)
  {
    matrix.data[matrix.n_rows - 1][j] = tmp_arr[(i + k) % size];
    i++;
  }
  for (int j = matrix.n_rows - 1; j >= 0; --j)
  {
    matrix.data[0][j] = tmp_arr[(i + k) % size];
    i++;
  }
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
  rotate_border(matrix, k);


  for (int r = 0; r < matrix.n_rows; ++r)
  {
    for (int c = 0; c < matrix.n_cols; ++c)
    {
      std::cout << matrix.data[r][c] << " ";
    }
    std::cout << std::endl;
  }

  destroy_matrix(matrix);
}