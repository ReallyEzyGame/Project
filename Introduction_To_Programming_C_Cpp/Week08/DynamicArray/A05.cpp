#include <stdio.h>

float find_meadian(const int *values, const int *freq, const int N)
{
    if (N % 2 == 0)
    {
        return 1.0 * (*(values + (N / 2) - 1) + *(values + (N / 2))) / 2;
    }
    else
    {
        return *(values + (N / 2));
    }
}

int main()
{
    int array1[10] = {1,2,2,2,3,4,5,5,6,7};
    int fre1[10] = {1,1,1,1,1,1,1,1,1,1};
    int array2[9] = {1,2,3,4,5,6,7,8,8};
    int fre2[9] = {1,1,1,1,1,1,1,1,1};

    for (int i = 0; i < 10; ++i) {
        printf("%d ", array1[i]);
    }
    printf("\nthe median of the array is: %.4f\n", find_meadian(array1,fre1, 10));

    for (int i = 0 ; i < 9; ++i) {
        printf("%d ", array2[i]);
    }
    printf("\nthe median of the array is: %.4f\n", find_meadian(array2, fre2, 9));
}