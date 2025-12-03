#include  <iostream>


struct Matrix {
  float** data;
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
void destroy_matrix(Matrix& matrix) {

  for (int r = 0; r < matrix.n_rows; ++r) {
    delete[] matrix.data[r];
  }

  delete[] matrix.data;
  matrix.data = nullptr;
  matrix.n_rows = matrix.n_cols = 0;
}


int count_saddle_point(const Matrix& matrix) {
  int max_on_rows_idx[matrix.n_rows];
  int min_on_cols_idx[matrix.n_cols];
  int cnt = 0;


  // Find all the max value index on rows
  for (int r = 0; r < matrix.n_rows; ++r) {
    int max = 0;
    for (int c = 1; c < matrix.n_cols; ++c) {
      if (matrix.data[r][max] < matrix.data[r][c]) {
        max = c;
      }
    }
    max_on_rows_idx[r] = max;
  }
  // Find all the min value index on column
  for (int c = 0; c < matrix.n_cols; ++c) {
    int min = 0;

    for (int r = 1; r < matrix.n_rows; ++r) {
      if (matrix.data[min][c] > matrix.data[r][c]) {
        min = r;
      }
    }
    min_on_cols_idx[c] = min;
  }


  for (int r = 0; r < matrix.n_rows; ++r) {
    for (int c = 0;  c < matrix.n_cols; ++c) {
      if (c == max_on_rows_idx[r] && r == min_on_cols_idx[c]) {
        cnt++;
      }
    }
  }

  return cnt;
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
int main() {
  int N, M;
  Matrix matrix;

  std::cout << "Input  size N,M: ";
  std::cin >> N >>  M;

  matrix = create_matrix(N,M);
  std::cout << "Number of Saddle Points: " << count_saddle_point(matrix) << std::endl;

  destroy_matrix(matrix);
}