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
// Output: 5.33

// Test case 2
// Input:
/*
    0
    27
*/
// Output: 0

// Test case 3
// Input:
/*
    5
    27
*/
// Output: 145.139

// Test case 4( Overflow Error Case)
// Input:
/*
    5
    2025
*/
// Output: -inf
// This test case show the liminal of the programm that cannot give the correct output when 'N' exceed more than 65
int main()
{
    int n;
    long long cur = 1, fac = 1;
    double x, sum = 0.f;

    std::cout << "Input X: ";
    std::cin >> x;

    std::cout << "Input N: ";
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        cur = cur * x;
        fac = fac * i;

        sum = sum + (1.0f * cur / fac);
    }

    std::cout << "result: " << std::setprecision(3) << sum << std::endl;
    system("pause");
}