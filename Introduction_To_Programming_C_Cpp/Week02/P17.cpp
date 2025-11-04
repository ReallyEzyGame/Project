#include <stdio.h>
#define NUMBER_MONEY_TYPE 9
/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// CLASS: 25CTT1B

// Test case 1
// Input: 1250000
// Output:
/*
        500000 : 2
        200000 : 1
        100000 : 0
        50000 : 1
        20000 : 0
        10000 : 0
        5000 : 0
        2000 : 0
        1000 : 0
 */
// Test case 2 (int type will be cast to unsigned value)
// Input: -1
// Output:
/*
        500000 : 8589
        200000 : 2
        100000 : 0
        50000 : 1
        20000 : 0
        10000 : 1
        5000 : 1
        2000 : 1
        1000 : 0
 */
// Test case 3
// Input: 0
// Output:
/*
        500000 : 0
        200000 : 0
        100000 : 0
        50000 : 0
        20000 : 0
        10000 : 0
        5000 : 0
        2000 : 0
        1000 : 0
 */
int main()
{
    unsigned long n;
    int money[NUMBER_MONEY_TYPE] = {500000, 200000, 100000, 50000, 20000, 10000, 5000, 2000, 1000};

    printf("Input Amount of Money: ");
    scanf("%lu", &n);

    int i = 0;
    while (i < NUMBER_MONEY_TYPE)
    {
        int number = n / money[i];
        n -= number * money[i];

        printf("\t%lu : %d\n", money[i], number);
        ++i;
    }
}