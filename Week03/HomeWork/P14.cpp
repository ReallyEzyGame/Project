#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input: 6 2024
// Ouptut: 30

// TESTCASE 2
// Input: 10 2025
// Ouptut: 31

// TESTCASE 3
// Input: 9 1954
// Ouptut: 30

bool isLeapYear(const int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// Odd months before august have 31 days and 30 days after it
// Even months before august have 30 days and 31 days after it
// Ferbuary has 28 days in normal year and 29 days in leap year
int main()
{
    int day, month, year;
    printf("Input month, year: ");
    scanf("%d %d", &month, &year);

    if (month < 8)
    {
        if (month == 2)
            day = isLeapYear(year) ? 29 : 28;
        else
        {
            if (month % 2 == 0)
                day = 30;
            else
                day = 31;
        }
    }
    else
    {
        if (month % 2 == 0)
            day = 31;
        else
            day = 30;
    }

    printf("Day in %d/%d: %d\n", month, year, day);
}