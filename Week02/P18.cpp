#include <stdio.h>

void swap(int &x, int &y)
{
    x = x ^ y;
    y = y ^ x;
    x = x ^ y;
}

int main()
{
    int x, y;
    printf("Input x & y to swap: ");
    scanf("%d %d", &x, &y);

    swap(x, y);

    printf("Swapped value: %d %d", x, y);
}