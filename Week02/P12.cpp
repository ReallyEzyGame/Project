#include <stdio.h>

#define TAX 0.1f
/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// CLASS: 25CTT1B

/* Test case 1
Input:
        5
        2000
Output:  11000.00
*/
/*
// Test case 2
// Input:   94729
            2198482347
// Output: 2290873295840477184.00
*/
/*
// Test case 3
// Input:   0
            10000
// Output: 0.00
*/

int main()
{
    int quantity;
    float price;

    printf("Input Quantity: ");
    scanf("%d", &quantity);

    printf("Input Price: ");
    scanf("%f", &price);

    if (quantity < 0 || price < 0)
    {
        printf("Error: Input value must be Greater than 0\n");
        return 1;
    }

    printf("+ Total Amount to be Paid: %.2f", quantity * price * (1 + TAX));
    return 0;
}