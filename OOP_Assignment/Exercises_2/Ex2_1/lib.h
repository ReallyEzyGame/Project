#include <stdio.h>
#include <cmath>
#include <string>

#define BYTE_SIZE 8


class Fraction
{
private:
    int numerator, denominator;

public:
    // Default Constructor with numerator(0), denominator(1)
    Fraction();
    // Assing for the numerator and denominator(1)
    Fraction(const int);
    Fraction(std::string);
    // Copy Constructor
    Fraction(const Fraction&);


    // Input from Keyboard
    void input();
    // Copy other's numerator & denominator
    void setNum(const Fraction);
    void setDenom(const int);
    // Display the Fraction to the Screen
    void output();
    Fraction &getNum();
    int getDenom();
    // reduce numerator & denominator
    Fraction reduce();
    Fraction inverse();
    Fraction add(const Fraction);
    int compare(const Fraction);
};



bool isDigit(const char ch);
int strToInteger(std::string);