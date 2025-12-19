#include <stdio.h>

void addOne(int *ptrNum)
{
    *ptrNum += 1;
}

int main()
{
    int value = 0;
    printf("Before Assigning: %d\n", value);

    addOne(&value);

    printf("After Assigning: %d", value);
}