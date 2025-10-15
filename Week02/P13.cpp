#include <stdio.h>
/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// CLASS: 25CTT1B

// Test case 1
// Input: 3.00 4.00 5.00
// Output: 12.00 6.00

// Test case 2
// Input: 6 8 10
// Output: 24.00 24.00

// Test case 3
// Input: 100000000 1000000000 1000000000
// Output: 2100000000.00 49937460196540416.00

#define PRECISION 16
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
    float edge1, edge2, edge3;

    printf("Input 3 Edges of the Triangle: ");
    scanf("%f %f %f", &edge1, &edge2, &edge3);

    // Using the Heron formula to calculate the Area of such triangle
    float p = (edge1 + edge2 + edge3) / 2.0f;
    float area = sqrt(p * (p - edge1) * (p - edge2) * (p - edge3));

    printf("\t+ Parameter: %.2f\n", 2.0 * p);
    printf("\t+ Area: %.2f", area);
}