#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input: 5
// Ouptut: 55

// TESTCASE 2
// Input: 11000000
// Ouptut: 17446248180768

// TESTCASE 3
// Input: 0
// Ouptut: 0

int main()
{
    int n;
    long long sum = 0;

    printf("Input n: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        sum += i * i;

    printf("Output: %lld\n", sum);
}