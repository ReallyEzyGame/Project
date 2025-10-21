#include <stdio.h>

/* Notice: the output of the program will produce some spcripts beside the requirement result so the output to the console will look like this
    + Paremeter: 24.00
    + Area: 24.00
*/
// But in the output we will only display the requirement result

// STUDENT ID: 24120409
// FULL NAME: LE THANH PHONG
// 25CTT1

// Test case 1
// Input: 42.195 1 59 40.2
// Output: 2.84 21.16

// Test case 2
// Input: 2974329432634 1223 1324 12434.242142
// Output: 0.00 2382283008.00

// Test case 3
// Input: 122 1 1 12.12
// Output: 0.50 119.60

int main()
{
    float distant; // Unit: kilometer( km)
    int hour, minute;
    float second;

    printf("Input distant( km), hour(s), minute(s), second(s): ");
    scanf("%f %d %d %f", &distant, &hour, &minute, &second);

    // Convere time to minute(s)
    float time = hour * 60 + minute + second / 60.f;

    printf("Pace: %.2f\tSpeed: %.2f\n", time / distant, distant * 60 / time);
}