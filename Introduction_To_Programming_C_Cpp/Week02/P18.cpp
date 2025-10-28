#include <stdio.h>
/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// CLASS: 25CTT1B

// Test case 1
// Input: 5 3
// Output: 3 5

// Test case 2
// Input: -10000 1999
// Output: 1999 -10000

// Test case 3
// Input: 0 1
// Output: 1 0

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