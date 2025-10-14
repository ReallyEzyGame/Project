#include <stdio.h>

/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// 25CTT1

// Test case 1
// Input:
// Output:
// Test case 2
// Input:
// Output:
// Test case 3
// Input:
// Output:

int main()
{
    float quota, max_cashback;

    printf("Input the percent & maximum amount of the cashback event: ");
    scanf("%f %f", &quota, &max_cashback);

    printf("the amount of money that the customer has to spend to get the maximun cashback is: %.f2\n", max_cashback * 1.0f / quota);
}