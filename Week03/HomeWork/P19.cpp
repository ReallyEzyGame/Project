#include <stdio.h>

#define LEVEL_1 3300 // the price when consumed does not execced 4 m^3
#define LEVEL_2 5200 // the price when consumed more than 4 to 6 m^3
#define LEVEL_3 7000 // the price when consumed higher

#define TAX 0.1

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input: 10 50 102
// Ouptut: 297440.00

// TESTCASE 2
// Input: 1 50 500
// Ouptut: 3465000.00

// TESTCASE 3
// Input: 129362959 91387113 27841721890490
// Ouptut: 15831943610368.00

int main()
{
    int person, previous, current;
    float consumed_per_person, price;

    printf("input number of person, previous and current m^3 of water has been consumed\n");
    scanf("%d %d %d", &person, &previous, &current);

    consumed_per_person = 1.0f * (current - previous) / person;

    price = (1 + TAX) * (current - previous);
    if (consumed_per_person <= 4)
    {
        printf("Water Bill: %.2f", price * LEVEL_1);
    }
    else if (consumed_per_person <= 6)
    {
        printf("Water Bill: %.2f", price * LEVEL_2);
    }
    else
    {
        printf("Water Bill: %.2f", price * LEVEL_3);
    }
}