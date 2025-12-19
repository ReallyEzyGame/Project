#include <stdio.h>

int doSomething(int *x, int *y)
{
    int temp = *x;
    *x = (*y) * 10;
    *y = temp * 10;

    return *x + *y;
}

int main()
{
    int val1 = 10, val2 = -10;

    printf("Before: %d and %d\n", val1, val2);

    doSomething(&val1, &val2);

    printf("After: %d and %d\n", val1, val2);
}