#include "lib.h"

int main()
{
    const int size1 = 8;
    int data1[8] = {1, 4, 6, 4, 3, 6, 8, 10};

    Array arr1;
    Array arr2(10);
    Array arr3(data1, size1);
    Array arr4(arr3);
    Array arr7;

    printf("Array made by Default Constructor: ");
    arr1.output();
    printf("\n");

    printf("Array made by Integer only Parameter: ");
    arr2.output();
    printf("\n");

    printf("Array made by Two Parameter Constructor: ");
    arr3.output();
    printf("\n");

    printf("Array made by Copy Constructor: ");
    arr4.output();
    printf("\n");

    printf("Sort the Array in Acsending Order: ");
    Array arr5(arr4.sort(smallerThan));
    arr5.output();
    printf("\n");

    printf("Sort the Array in Descending Order: ");
    Array arr6(arr4.sort(greaterThan));
    arr6.output();
    printf("\n");

    arr7.input();
    printf("Araray input by user: ");
    arr7.output();
    printf("\n");

}