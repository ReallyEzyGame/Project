#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input: 1500000 1 2
// Ouptut: 1530000.00

// TESTCASE 2
// Input: 1500000 2 2
// Ouptut: 1560600.00

// TESTCASE 3
// Input: 109274280 25 6
// Ouptut: 468990432.00

int main()
{
    int save, month, q;
    float rate;
    float profit;

    printf("Input amount of saving money, number of saving month, the rate: ");
    scanf("%d %d %d", &save, &month, &q);

    rate = 1.0f * q / 100.f;
    profit = save;
    for (int i = 1; i <= month; ++i)
        profit *= (1 + rate);

    printf("Amount of profit: %.2f\n", profit);
    return 0;
}