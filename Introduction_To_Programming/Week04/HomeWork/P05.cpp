#include <iostream>
#include <iomanip>

// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input: 5
// Output: 1.88

// Test case 2
// Input: 0
// Output: 1

// Test case 3 ( Underflow Test case)
// Input: 274234343
// Output: 10.7

int main()
{
    int n;
    double sum = 0;

    std::cout << "Input N: ";
    std::cin >> n;

    for (int i = 0; i <= n; ++i)
    {
        sum += 1.0f / (2 * i + 1);
    }

    std::cout << "result: " << std::setprecision(3) << sum << std::endl;

    system("pause");
}