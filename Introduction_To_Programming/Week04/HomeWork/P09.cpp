#include <iostream>

// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input: 5
// Output: 120

// Test case 2
// Input: 0
// Output: 1

// Test case 3
// Input: 27
// Output: 12963097176472289280

// Test case 4 ( Overflow Test case)
// Input: 2745656553
// Output: 0
// This test case happens because oveflow has occured when the n is too big that the factorial cannot be contained an unsigned long long type

int main()
{
    int n;
    unsigned long long fac = 1;

    std::cout << "Input N: ";
    std::cin >> n;

    n = n >= 1 ? n : 1; // Clamp to Avoid Negative case

    for (int i = 1; i <= n; ++i)
        fac *= i;

    std::cout << fac << std::endl;

    system("pause");
}