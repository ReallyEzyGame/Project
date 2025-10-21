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
// Input: 10000
// Output: 0

// Test case 2
// Input: 99999
// Output: 5

// Test case 3
// Input: 12345
// Output: 5

int countPlate(int plate)
{
    int cnt = 0;
    while (plate > 0)
    {
        cnt = cnt + plate % 10;
        plate /= 10;
    }

    return cnt;
}
int main()
{
    int plate;
    printf("Input Plate Number: ");
    scanf("%d", &plate);

    printf("%d", countPlate(plate) % 10);
}