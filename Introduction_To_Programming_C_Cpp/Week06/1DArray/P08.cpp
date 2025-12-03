#include <iostream>



/*
  STUDENT'S ID: 24120409
  STUDENT NAME: Le Thanh Phong
  CLASS: 25CTT1B/24CTT3
*/

/*
  Test Case 01
  Input:
          7 3 2
          12 67 45 87 678 0 2
  Output: 12 67 45 0 2
*/
/*
  Test Case 02
  Input:
          7 2 1
          12 67 45 87 678 0 2
  Output: 12 67 87 678 0 2
*/
/*
  Test Case 03
  Input:
          10 3 4
          9 18 76 87 54 65 67 34 23 21
  Output: 9 18 76 34 23 21
*/


int *remove_k_consecutive(const int *array, const int N, const int idx, const int k, int& size)
{
  int M = N - k;

  int *new_arr;
  if (M <= 0)
  {
    return nullptr;
  }
  else if (idx < 0 || N <= idx)
  {
    new_arr = new int[N];

    for (int i = 0; i < N; ++i)
    {
      new_arr[i] = array[i];
    }
    size = N;
  }
  else
  {
    new_arr = new int[M];

    for (int i = 0; i < idx; ++i)
    {
      new_arr[i] = array[i];
    }
    for (int i = idx; i < M; ++i)
    {
      new_arr[i] = i + k >= N ?  0 : array[i + k];
    }
    size = M;
  }

  return new_arr;
}
int main()
{
  int N, idx, k;
  int *array;

  std::cout << "Input Size, remove index, k partical: ";
  std::cin >> N >> idx >> k;
  array = new int[N];

  for (int i = 0; i < N; ++i)
  {
    int num;

    std::cin >> num;
    array[i] = num;
  }

  int size;
  int* shorted_arr = remove_k_consecutive(array, N, idx, k,size);
  for (int i = 0; i < size; ++i) {
    std::cout << shorted_arr[i] << " ";
  }
  std::cout << std::endl;


  delete[] array;
  delete[] shorted_arr;
}