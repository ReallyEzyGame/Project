#include <stdio.h>
#include <math.h>

// Student ID: 24120409
// FullName: Le Thanh Phong
// Class: 25CTT1B/ 24CTT3

// TESTCASE 1
// Input: 2 -7 5
// Ouptut: x1 = 2.50, x2 = 1.00

// TESTCASE 2
// Input: 1 1 1
// Ouptut: The result of the equation is not belongs to Real number set

// TESTCASE 3
// Input: 1 3 2
// Ouput: x1 = -1.00, x2 = -2.00

int main()
{
    float a, b, c, delta;
    float x1, x2;
    printf("Solve for a*x^2 + b * x + c = 0 equation\n");
    printf("Input a, b, c: ");
    scanf("%f %f %f", &a, &b, &c);

    delta = b * b - 4 * a * c;

    if (delta > 0)
    {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);

        printf("x1 = %.2f, x2 = %.2f\n", x1, x2);
    }
    else if (delta == 0)
    {
        x1 = x2 = -b / (2 * a);
        printf("x1 = x2 = %.2f\n", x1);
    }
    else
    {
        printf("The result of the equation is not belongs to Real number set\n");
    }
    return 0;
}