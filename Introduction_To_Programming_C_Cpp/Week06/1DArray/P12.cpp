#include <iostream>

/*
  STUDENT'S ID: 24120409
  STUDENT NAME: Le Thanh Phong
  CLASS: 25CTT1B/24CTT3
*/

/*
  Test Case 01
  Input:
          10
          1 2 3 4 5 6 7 8 9 10
  Output: 9
*/
/*
  Test Case 02
  Input:
          8
          5 12 5 45 87 678 5 1
  Output: 87
*/
/*
  Test Case 03
  Input:
          7
          3 5 12 67 67 45 678
  Output: 67
*/

int find_second_largest(int* array, const int N) {
  int max = array[0], sec_max = array[0];

  for (int i = 0; i < N; ++i) {
    if (array[i] > max) {
      sec_max = max;
      max = array[i];
    }
  }

  return sec_max;
}
int main() {
  int N;
  int* array;

  std::cout  << "Input Size: ";
  std::cin >> N;
  array = new int[N];

  for (int i = 0; i < N; ++i) {
    int num;

    std::cin >> num;
    array[i] = num;
  }

  std::cout << find_second_largest(array, N) << std::endl;
  delete[] array;
}