#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// Test case 1
// Input: 2 7 5 12
// Output: 12 2

// Test case 2
// Input: 97248975285294 -913742234 0 1
// Output: 2147483647 -913742234

// Test case 3(int overflow case)
// Input: 9276529507249562 192740984724723 19084719247219 12874252134012
// Output: 9276529507249562 12874252134012

long long max(const long long a, const long long b)
{
    return a > b ? a : b;
}
long long min(const long long a, const long long b)
{
    return a < b ? a : b;
}
int main()
{
    long long a, b, c, d;
    printf("Input 4 long longeger values: ");
    scanf("%lld %lld %lld %lld", &a, &b, &c, &d);

    long long maximum = max(a, max(b, max(c, d)));
    long long minimun = min(a, min(b, min(c, d)));

    printf("the Maximun and Minimun value: %lld %lld", maximum, minimun);

    return 0;
}