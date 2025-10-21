#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// Test case 1
// Input: 2019
// Output: Khong phai nam nhuan

// Test case 2
// Input: 2020
// Output: Nam nhuan

// Test case 3
// Input: 1800
// Output: Khong phai nam nhuan

int main()
{
    int year;
    bool leap_year;

    printf("Nhap vao nam can xet: ");
    scanf("%d", &year);

    leap_year = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? true : false;

    if (leap_year)
    {
        printf("Nam Nhuan\n");
    }
    else
        printf("Khong phai nam nhuan\n");
}