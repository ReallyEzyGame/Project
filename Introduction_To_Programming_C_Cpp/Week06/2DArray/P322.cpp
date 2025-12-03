#include <iostream>

// Number of input must be guarentee n_rows * n_cols
// Return a matrix has the size of: n_rows * n_cols
// The function will allocate the memory but will NOT delete it
float **create_matrix(const int n_rows, const int n_cols)
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
  return matrix;
}
void destroy_matrix(float **&matrix, const int n_rows) {

  for (int r = 0; r < n_rows; ++r) {
    delete[] matrix[r];
  }

  delete[] matrix;
  matrix = nullptr;
}


float *sum_row(const float **matrix, const int n_rows, const int n_cols)
{
  float *rows = new float[n_rows];

  for (int i = 0; i < n_rows; ++i)
  {
    float sum = 0;
    for (int j = 0; j < n_cols; ++j)
    {
      sum += matrix[i][j];
    }
    rows[i] = sum;
  }
  return rows;
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
  int N, M;
  std::cout << "Input Matrix size: ";
  std::cin >> N >> M;

 float** matrix =  create_matrix(N,M);
 float* rows = sum_row(matrix, N, M);

 for (int i = 0; i < N; ++i) {
  std::cout << rows[i] << " ";
 }
 std::cout << std::endl;

 destroy_matrix(matrix, N);
 delete[] rows;
}