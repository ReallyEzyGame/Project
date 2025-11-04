#include <iostream>

// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Test case 1
// Input: 6
// Output: 4

// Test case 2
// Input: 0
// Output: 0

// Test case 3
// Input: 187852594
// Output: 4

int find_total_divisor(int n)
{
    int cnt = 0;
    if (n > 0)
    {

        for (int i = 1; i <= n; ++i)
        {
            if (n % i == 0)
                cnt++;
        }
    }

    return cnt;
}

int main()
{
    int n;
    scanf_s("%d", &n);
    printf("%d", find_total_divisor(n));
}