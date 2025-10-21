#include <stdio.h>

#define PI 3.14
#define PRECISION 16

/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// 25CTT1B

// Test case 1
// Input: 3 2
// Output: 17.97

// Test case 2
// Input: 0192301474374 981374397
// Output: 48039757613572632346624.00

// Test case 3
// Input: 5 19
// Output: 1133.54

// Using Binary Search to find the correct value
float sqrt(float val)
{
    float mid;
    float upper = val, lower = 0;

    int i = 0;

    while (i <= PRECISION && lower < upper)
    {
        mid = lower + (upper - lower) / 2.0f;
        if (mid * mid > val)
        {
            upper = mid;
        }
        else if (mid * mid < val)
        {
            lower = mid;
        }
        else
            return mid;
    }
    i++;
    return mid;
}

int main()
{
    float edge, radius;
    printf("Input the edge of the triangle & circle Radius: ");
    scanf("%f %f", &edge, &radius);

    if (edge <= radius)
        printf("Area: %.2f\n", PI * radius * radius);
    else
    {
        float cir_area = PI * radius * radius;
        float tri_area = 3 * (edge * edge * sqrt(3) / 4.0f);
        float compliment = 3 * (1.0f / 6 * cir_area);

        printf("Area: %.2f\n", cir_area + tri_area - compliment);
    }
}