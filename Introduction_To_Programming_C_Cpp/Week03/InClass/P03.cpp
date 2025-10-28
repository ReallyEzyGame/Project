#include <stdio.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// Test case 1
// Input:
/*
    9.5
    8.5
    8.0
    0
*/
// Output: 8.6 PASSED

// Test case 2
// Input:
/*
    10
    10
    10
    10
    1
*/
// Output: 0.0 FAILED

// Test case 3
// Input:
/*
    5
    5
    5
    5
    0
*/
// Output: 5/0 PASSED

int main()
{
    float assignment, practice, theory; // Marks
    int isCheating;                     // Cheating  => 0.f
    // Input
    printf("Input Assigment Mark: ");
    scanf("%f", &assignment);

    printf("Input Practice Mark: ");
    scanf("%f", &practice);

    printf("Input Theory Mark: ");
    scanf("%f", &theory);

    printf("Cheating: ");
    scanf("%d", &isCheating);

    // Calculate and return the result
    float mark = isCheating ? 0.f : 0.3 * assignment + 0.3 * practice + 0.4 * theory;

    printf("%.1f ", mark);
    if (mark >= 5)
        printf("PASSED\n");
    else
        printf("FAILED\n");

    return 0;
}