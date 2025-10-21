#include <stdio.h>

/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// 25CTT1B

// Test case 1
// Input: 40 100000
// Output: 250000.00

// Test case 2
// Input: 38.32 194723948
// Output: 508152288.00

// Test case 3
// Input: 0 500000
// Output: There is no discount

int main()
{
    float quota, max_cashback;

    printf("Input the percent & maximum amount of the cashback event: ");
    scanf("%f %f", &quota, &max_cashback);

    if (quota <= 0)
    {
        printf("There is no discount\n");
        return 0;
    }
    printf("the amount of money that the customer has to spend to get the maximun cashback is: %.2f\n", max_cashback * 1.0f / (quota / 100));
}