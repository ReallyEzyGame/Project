#include <iostream>

// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input: 5
// Output: 25

// Test case 2
// Input: 0
// Output: 0

// Test case 3 ( Overflow Test case)
// Input: 39734905
// Output: 1578862675359025

int main()
{
    int n;
    long long sum = 0;

    std::cout << "Input N: ";
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        sum += n;
    }

    std::cout << "result: " << sum << std::endl;

    system("pause");
}