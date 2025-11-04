#include <stdio.h>
#include <math.h>

#define PI 3.14
#define E 2.71
/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// CLASS: 25CTT1B

// Test case 1
// Input: 10
// Output: 1788.9110640674 0.0000000217

// Test case 2
// Input: 1
// Output: 60.0000000000 0.1758440388

// Test case 3
// Input: 13
// Output: 2710.8866632413 0.0000000001

int main()
{
    double x;
    printf("Input x: ");
    scanf("%lf", &x);

    double a = 4 * (pow(x, 2) + 10 * x * sqrt(x) + 3 * x + 1);
    double b = (sin(PI * pow(x, 2)) + sqrt(pow(x, 2) + 1)) / (pow(E, 2 * x) + cos((PI / 4.0f) * x));

    printf("Result: %.10lf %.10lf", a, b);
}