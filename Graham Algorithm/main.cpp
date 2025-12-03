#include "lib.h"
#include <vector>
#include <stack>
#include <math.h>

// Max heap
template <typename  T>
void heapify(std::vector<T>& maps,const int cur,const int range) {
  int largest = cur;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;


  if (left <= range && maps[cur] <  maps[left]) {
    std::swap(maps[cur], maps[left]);
    largest = left;
  }
  if (right <= range && maps[cur] < maps[right]) {
    std::swap(maps[cur], maps[right]);
    largest = right;
  }


  if (cur != largest) {
    heapify(maps, largest, range);
  }
}
// Acsending Order
template <typename T>
std::vector<T> heapSort(std::vector<T> maps) {
  int N = maps.size();

  for (int i = N / 2 - 1; i >= 0; --i) {
    heapify(maps, i, N - 1);
  }
  for (int i = N - 1; i >= 0; --i) {
    std::swap(maps[0], maps[i]);
    heapify(maps, 0, i);
  }

  return maps;
}


float arccos(const float tan) {
  const int PRECISION = 15;
  int lower = INT_MIN, upper = INT_MAX, mid;

  while (mid != tan) {
    mid = lower + (upper -  lower) / 2;

    if (mid > tan) {
      upper = mid;
    }
    else if (mid < tan) {
      lower = mid;
    }
    else {
      return mid;
    }
  }
  return mid;
}
// return a vector of values between 0 and pi
std::vector<float> toRadiant(std::vector<Cordinate> maps,const Cordinate root) {
  std::vector<float> radiants;
  for (Cordinate cord : maps) {
    float l = sqrt(pow((cord.x - root.x), 2) + pow(cord.y - root.y, 2));
    float radiant = arccos((cord.x - root.x) / l);

    radiants.push_back(radiant);
  }
  return radiants;
}

Stack GrahamAlgorithm(const std::vector<Cordinate> maps) {
  // find the lowest point
  Cordinate root = maps[0];
  for (Cordinate cor : maps) {
    if (cor.y < root.y) {
      root = cor;
    }
    else if (cor.y == root.y) {
      if (cor.x < root.x) {
        root = cor;
      }
    }
  }
  // Change to radiant unit with the root cordinate to use the graham algorithm
  std::vector<float> radiants = toRadiant(maps, root);
  // Acsending Order
  radiants = heapSort<float>(radiants);
  std::stack<float> stk;

  for (float rad : radiants) {
    bool flag = false;
    while (!flag) {
      if (stk.size() <= 2) {
        stk.push(rad);
      }
      
      float cross_prod = () * ()
    }
  }
}