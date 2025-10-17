#include <stdio.h>
#include <cmath>
#include <string>

// The Soruce code of the Fraction is reused from the previous exercise on week 2(ex21) and extern more methods such as constructor, desrtuctor, etc...
class Fraction
{
private:
    static int count;
    int numer, denom;

    void countObject();

public:
    Fraction();
    Fraction(const int);
    Fraction(const int, const int);
    Fraction(const std::string);
    Fraction(const Fraction &);

    // Input from Keyboard
    void input();
    // Display the Fraction to the Screen
    void output();

    // Copy other's numerator & denominator
    void setNum(const Fraction);
    void setDenom(const int);

    Fraction &getNum();
    int getDenom();
    // return the number of Fraction class object has been created
    int getNumberOfObject();

    // reduce numerator & denominator
    Fraction reduce();
    Fraction inverse();
    Fraction add(const Fraction);
    int compare(const Fraction);
};