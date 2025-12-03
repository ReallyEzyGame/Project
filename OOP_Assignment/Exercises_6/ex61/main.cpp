#include "lib.h"


int main() {
  int int_arr[6] = {1,2,2,33,4,4};
  int int_arr2[10] = {1,1,1,1,1,1,1,1,1,1};

  Array arr1(int_arr, 6);

  arr1.display();

  
  HistogramArray hist1(arr1);
  HistogramArray hist2(int_arr2, 10);
  printf("\n");
  hist1.display();

  printf("\nBefore Changing\n");
  hist2.display();
  printf("\nAfter Changing\n");
  hist2[0] = 10000;
  hist2.display();

}