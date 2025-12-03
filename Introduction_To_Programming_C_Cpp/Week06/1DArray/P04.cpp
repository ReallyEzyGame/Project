#include <iostream>

/*
  STUDENT'S ID: 24120409
  STUDENT NAME: Le Thanh Phong
  CLASS: 25CTT1B/24CTT3
*/

/*
  Test Case 01
  Input:
          7
          12 67 45 87 678 0 2
  Output: 67 2
*/
/*
  Test Case 02
  Input:
          7
          3 5 12 67 80 45 678
  Output: 3 5 67
*/
/*
  Test Case 03
  Input:
          5
          2 6 1 4 7
  Output: 2 7 
*/
bool isPrime(const int number) {
  if (number <= 1) {
    return false;
  }

  for (int i = 2; i* i <= number; ++i) {
    if (number % i == 0) {
      return  false;
    }
  }
  return true;
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

  for (int i = 0; i < N; ++i) {
    if (isPrime(array[i])) {
      std::cout << array[i] << " ";
    }
  }
  std::cout << std::endl;
  delete[] array;
}