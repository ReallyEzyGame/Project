#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input: 6
// Ouptut: 1 2 3 6

// TESTCASE 2
// Input: 9827529422
// Ouptut: 1 2 17 34 14549 19867 29098 39734 247333 337739 494666 675478 289044983 578089966 4913764711 9827529422

// TESTCASE 3
// Input: 12980237
// Ouptut: 1 139 93383 12980237

int main()
{
    unsigned long long n;
    printf("Input n: ");
    scanf("%llu", &n);

    for (unsigned long long i = 1; i <= n; ++i)
        if (n % i == 0)
            printf("%llu ", i);
    printf("\n");

    return 0;
}