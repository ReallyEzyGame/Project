#include "lib.h"



int main() {
    Fraction frac1;
    Fraction frac2(5);
    Fraction frac3;
    Fraction frac4("9/6");
    Fraction frac5("-100/15");
    Fraction frac6;

    printf("The Fraction using Default Constructor: ");
    frac1.output();
    printf("\n");

    printf("The Fraction using Integer Parameter: ");
    frac2.output();
    printf("\n");

    printf("The Fraction using Copy Constructor: ");
    frac3.output();
    printf("\n");

    printf("The Fraction using str Constructor: ");
    frac4.output();
    printf("\n");

    printf("The Fraction: ");
    frac1.output();
    printf(" + ");
    frac4.output();
    printf(" = ");
    frac1.add(frac4).output();
    printf("\n");

    printf("The Inverse of ");
    frac5.output();
    printf(" is ");
    frac5.inverse().output();
    printf("\n");

    printf("The Reduce of ");
    frac5.output();
    printf(" is ");
    frac5.reduce().output();
    printf("\n");

    frac6.input();
    printf("Input Fraction: ");
    frac6.output();
    printf("\n");
    
}


