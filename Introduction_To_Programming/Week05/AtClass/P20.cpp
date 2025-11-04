#include <iostream>

// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input: 6
// Output: 1 2 3 6

// Test case 2
// Input: 0
// Output:     (empty)

// Test case 3
// Input: 187852594
// Output: 1 2 93926297 187852594

int main()
{
    int n;

    std::cout << "Input N: ";
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        if (n % i == 0)
            std::cout << i << " ";
    }
    std::cout << std::endl;

    system("pause");
}