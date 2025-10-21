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
// Input: 1000 1211
// Output: 211

// Test case 2
// Input: 3540129 3600000
// Output: 59871

// Test case 3
// Input: 199 200
// Output: 1

int main()
{
    int prev, curr;
    printf("\tInput the Electricity Consumed\n");
    printf("\t+ Input Previous Month & Current Month Consumed: ");
    scanf("%d %d", &prev, &curr);

    if (prev < 0 || curr < 0 || prev > curr)
    {
        printf("Error: the previous consumed cannot be greater than current consumed\n");
        return 1;
    }

    printf("Electricity Consumed: %d", curr - prev);
}