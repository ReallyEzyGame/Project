#include <iostream>
#include <iomanip>

// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input:
/*
    2
    3
*/
// Output: 84

// Test case 2
// Input:
/*
    -100
    100
*/
// Output: 4.99e+18

// Test case 3
// Input:
/*
    2
    1239085
*/
// Output: 6.15e+18

int main()
{
    int x, n;
    long long cur = 1;
    double sum = 0;

    std::cout << "Input X: ";
    std::cin >> x;

    std::cout << "Input N: ";
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        cur *= x * x;
        sum += cur;
    }

    std::cout << "result: " << std::setprecision(3) << sum << std::endl;
    system("pause");
}