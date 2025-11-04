#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input:
/*
    1 1 4 3
    4 5
*/
// Ouptut: C does not belongs to the Rectangle

// TESTCASE 2
// Input:
/*
    1 1 4 3
    2 3
*/
// Ouptut: C belongs to the Rectangle

// TESTCASE 3
// Input:
/*
    0 0 10294723047 124720497
    9274049023 2947792492
*/
// Ouptut: C does not belongs to the Rectangle

// decide if the 3rd parameter value is between the first two value
int isInBetween(const int a, const int b, const int c)
{
    return (a <= c && c <= b) || (b <= c && c <= a);
}
int main()
{
    int a1, a2, b1, b2;
    int c1, c2;
    printf("Input a, b 2D cordinate: ");
    scanf("%d %d %d %d", &a1, &a2, &b1, &b2);

    printf("Input c 2D cordinate: ");
    scanf("%d %d", &c1, &c2);

    if (isInBetween(a1, b1, c1) && isInBetween(a2, b2, c2))
    {
        printf("C belongs to the Rectangle\n");
    }
    else
    {
        printf("C does not belongs to the Rectangle\n");
    }

    return 0;
}