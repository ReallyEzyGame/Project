#include <iostream>

/*
  STUDENT'S ID: 24120409
  STUDENT NAME: Le Thanh Phong
  CLASS: 25CTT1B/24CTT3
*/

/*
  Test Case 01
  Input:
          10 10
          1 2 3 4 5 6 7 8 9 10 10 9 8 7 6 5 4 3 2 1
  Output: 1 2 3 4 5 6 7 8 9 10
*/
/*
  Test Case 02
  Input:
          7 6
          3 5 12 67 80 45 678 5 23 12 45 56 67
  Output: 5 12 67 45
*/
/*
  Test Case 03
  Input:
          7 6
          3 5 12 67 67 45 678 5 23 12 45 12 67
  Output: 5 12 67 45
*/


struct Array
{
  int* data;
  int size;
};


void find_common_value(const Array array1, const Array array2) {
  bool visited[array2.size];
  for (int i = 0; i < array2.size; ++i)  {
    visited[i]  =  false;
  }

  for (int i = 0; i < array1.size; ++i) {
    bool flag = false;

    for (int j = 0; j < array2.size; ++j) {
      if (array1.data[i] == array2.data[j] && !visited[j]) {
        flag = true;
        visited[j] = true;
      }
    }
    
    if (flag) {
      std::cout << array1.data[i] << " ";
    }
  }
  std::cout << std::endl;
}



int main() {
  int N, M;
  int *array1, *array2;

  std::cout  << "Input Size N, M: ";
  std::cin >> N >> M;
  array1 = new int[N];
  array2 = new int[M];

  for (int i = 0; i < N; ++i) {
    int num;

    std::cin >> num;
    array1[i] = num;
  }
  for (int i = 0; i < M; ++i) {
    int num;

    std::cin >> num;
    array2[i] = num;
  }

 
  find_common_value({array1, N}, {array2,M});
  delete[] array1;
  delete[] array2;
}