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


void insertion_sort(float*& array,const int N) {
  for (int i = 1; i < N; ++i) {
    int j = i;
    int tmp = array[j];

    while (j >= 0 && array[j - 1] > tmp) {
      array[j] = array[j - 1];
      j--;
    }
    array[j + 1] = tmp;
  }
}

Matrix create_spiral_matrix(float* arr,const int N,const int n_rows,const int n_cols) {
  int upper = 0, lower = n_rows - 1;
  int left = 0, right = n_cols - 1;
  int idx = 0;

  float **matrix = new float *[n_rows];
  for (int i = 0; i < n_rows; ++i)
  {
    matrix[i] = new float[n_cols];
  }


  while (true) {
    // Fill the top
    for (int i = left; i <= right; ++i) {
      matrix[upper][left] = arr[idx++];
    }
    upper += 1;
    if (idx >= N)
    {
      break;
    }
    // Fill the right
    for (int i = upper; i <= lower; ++i) {
      matrix[i][right] = arr[idx++];
    }
    right -= 1;
    if (idx >= N)
    {
      break;
    }
    // Fill the bottom
    for (int i = right; i >= 0; --i) {
      matrix[lower][i] = arr[idx++];
    }
    lower -= 1;
    if (idx >= N)
    {
      break;
    }
    // Fill the left
    for (int i = lower; i >= 0; --i) {
      matrix[left][i] = arr[idx++];
    }
    left += 1;
    if (idx >= N)
    {
      break;
    }
  }

  return Matrix{matrix, n_rows, n_cols};
}
Matrix make_spiral_matrix(const Matrix& matrix) {
  int k = 0;
  int size = matrix.n_rows * matrix.n_cols;
  float* tmp_arr = new float[size];

  for (int i = 0; i < matrix.n_rows; ++i) {
    for (int j = 0; j < matrix.n_cols; ++j) {
      tmp_arr[k++] = matrix.data[i][j];
    }
  }
  // Sort the Array
  insertion_sort(tmp_arr, size);
  Matrix spiral = create_spiral_matrix(tmp_arr, size, matrix.n_rows, matrix.n_cols);

  delete tmp_arr;
  return spiral;
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

  std::cout << "Input  size N,M: ";
  std::cin >> N >> M >> k;

  matrix = create_matrix(N, M);
  Matrix spiral = make_spiral_matrix(matrix);

  for (int r = 0; r < spiral.n_rows; ++r)
  {
    for (int c = 0; c < spiral.n_cols; ++c)
    {
      std::cout << spiral.data[r][c] << " ";
    }
    std::cout << std::endl;
  }
  
  destroy_matrix(matrix);
  destroy_matrix(spiral);
}