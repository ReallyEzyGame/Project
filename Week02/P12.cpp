#include <stdio.h>

#define TAX 0.1f
/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// 25CTT1

// Test case 1
// Input:
// Output:
// Test case 2
// Input:
// Output:
// Test case 3
// Input:
// Output:

int main()
{
    int quantity;
    float price;

    printf("Input Quantity: %d", &quantity);
    printf("Input Price: %f", price);

    if (quantity < 0 || price < 0)
    {
        printf("Error: Input value must be Greater than 0\n");
        return 1;
    }

    printf("+ Total Amount to be Paid: %.2f", quantity * price * (1 + TAX));
    return 0;
}