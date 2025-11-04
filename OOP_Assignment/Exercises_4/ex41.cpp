#include <stdio.h>
#include <istream>
#include <ostream>

#include <cmath>
#include <string>

// Convere a string of number to Integer
int toInteger(const std::string str) {
    int num = 0, idx = 0;
    bool negative = (str[idx] == '-') ? true : false;

    if (negative) idx++;


    while (idx < str.size()) {
        num = num * 10 + (str[idx++] - '0');
    }

    return (negative) ? - num : num;
}


// The Soruce code of the Fraction is reused from the previous exercise on week 2(ex21) and extern more methods such as constructor, desrtuctor, etc...
class Fraction
{
private:
    int numer, denom;

public:
    Fraction();
    Fraction(const int);
    Fraction(const int, const int);
    Fraction(const std::string);
    Fraction(const Fraction&);

    // Input from Keyboard
    void input();
    // Display the Fraction to the Screen
    void output();

    
    // Copy other's numerator & denominator
    void setNum(const Fraction);
    void setDenom(const int);

    Fraction &getNum();
    int getDenom();
    
    // reduce numerator & denominator
    Fraction reduce();
    Fraction inverse();


    // Arithmetic
    Fraction operator+ (const Fraction);
    Fraction operator- (const Fraction);
    Fraction operator* (const Fraction);
    Fraction operator/ (const Fraction);
    // Comparision
    bool operator> (const Fraction);
    bool operator>= (const Fraction);
    bool operator< (const Fraction);
    bool operator<= (const Fraction);
    bool operator== (const Fraction);
    // Assigment
    Fraction& operator= (const Fraction);
    // Increment & Decrement
    Fraction& operator+= (const Fraction);
    Fraction& operator-= (const Fraction);
    Fraction& operator*= (const Fraction);
    Fraction& operator/= (const Fraction);
    // type-cast
    float operator= (float);
    int operator= (int);
    // Input - Ouptut
    friend std::istream& operator>>(std::istream&,const Fraction&);
    friend std::ostream& operator<<(std::ostream&,const Fraction);
};



Fraction::Fraction(): numer(0), denom(1) {}
Fraction::Fraction(const int num, const int den) {
    if (den == 0) {
        printf("Error: Denominator cannot be 0\n");
        printf("Default Denominator to 1\n");

        denom = 1;
    }
    else denom = den;

    numer = num;
}
Fraction::Fraction(const int num) : numer(num), denom(1) {}
Fraction::Fraction(const std::string frac) {
    int i = 0;
    int n,d;

    // Find the char '\' & get the numerator
    for (; i < frac.size() && frac[i] != '/'; ++i);

    // char '\' does not exist
    if (i == frac.size()) {
        printf("Error: Expected '\\'\n");
        *this = Fraction();
    }

    n = toInteger(frac.substr( 0, i - 1));
    d = toInteger(frac.substr(++i, frac.size() - i));

    if (d == 0) {
        printf("Error: Denominator cannot be 0\n");
        printf(" Default Fraction as 0 / 1");
        *this = Fraction();

        return;
    }

    if (n < 0 ||  d < 0)
        n *= (d < 0) ? -1 : 1;

    numer = n;
    denom = d;
} 
Fraction::Fraction(const Fraction& other) {
    numer = other.numer;
    denom = other.denom;
}
void Fraction::input()
{
    int numer, denom;
    scanf("Input Numerator & Denominator: %d %d", &numer, &denom);

    if (denom == 0)
    {
        printf("Error: Denominatior cannot be 0\n");
        return;
    }

    numer = numer;
    denom = denom;
}
void Fraction::output()
{
    printf("%d/%d", numer, denom);
}
Fraction &Fraction::getNum()
{
    return *this;
}
void Fraction::setNum(const Fraction other)
{
    numer = other.numer;
    denom = other.denom;
}
int Fraction::getDenom()
{
    return denom;
}
void Fraction::setDenom(const int value)
{
    if (value == 0)
    {
        printf("Error: Denominator cannot be 0\n");
    }
    else
        denom = value;
}
Fraction Fraction::reduce()
{
    bool numerSign = numer < 0;   // Numerator's Sign
    bool denomSign = denom < 0; // Denom's Sign

    numer = abs(numer);
    denom = abs(denom);

    for (int i = 2; i * i < numer && i * i < denom; ++i)
    {
        if (numer % i == 0 && denom % i == 0)
        {
            numer /= i;
            denom /= i;
        }
    }

    if (numerSign xor denomSign)
        numer *= -1  ;

    return *this;
}
Fraction Fraction::inverse() {
    // Swap numerator & denominator
    int temp = numer;
    numer = denom;
    denom = numer;

    return *this;
}



Fraction Fraction::operator+(const Fraction other) {
    Fraction number;

    number.numer = numer *  other.denom + denom * other.numer;
    number.denom = denom * other.numer;

    return number;

}
Fraction Fraction::operator-(const Fraction other) {
    Fraction number;

    number.numer = numer *  other.denom - denom * other.numer;
    number.denom = denom * other.numer;

    return number;
}
Fraction Fraction::operator*( const Fraction other) {
    Fraction number;

    number.numer = numer * other.numer;
    number.denom = denom * other.denom;

    return number;
}
Fraction Fraction::operator/( const Fraction other) {
    Fraction number;
    // Error  case
    if (other.numer == 0) {
        printf("Error: Unable to Divide by 0\n");
        return number;
    }

    number.numer = numer * other.denom;
    number.denom = denom * other.numer;

    return number;
}


bool Fraction::operator< (const Fraction other) {
    return ((*this) - other).numer <  0;
}
bool Fraction::operator<= (const Fraction other) {
    return ((*this) - other).numer <= 0;
}
bool Fraction::operator== (const Fraction other) {
    return ((*this) - other).numer == 0;
}
bool Fraction::operator> (const Fraction other) {
    return ((*this) - other).numer > 0;
}
bool Fraction::operator>= (const Fraction other) {
    return  ((*this) - other).numer >= 0;
}

Fraction& Fraction::operator= (const Fraction other) {
    this->numer = other.numer;
    this->denom = other.denom;

    return *this;
}
float Fraction::operator= (float) {
    return 1.0f * this->numer / this->denom;
}
int Fraction::operator= (int) {
    return  this->numer / this->denom;
}
Fraction& Fraction::operator+= (const Fraction other) {
    this->numer = this->numer * other.denom + this->denom * other.numer;
    this->denom = this->denom * other.denom;

    return *this;
}
Fraction& Fraction::operator-= (const Fraction other) {
    this->numer = this->numer * other.denom - this->denom * other.numer;
    this->denom = this->denom * other.denom;

    return *this;
}
Fraction& Fraction::operator*= (const Fraction other) {
    this->numer = this->numer * other.numer;
    this->numer = this->denom * other.denom;

    return *this;
}
Fraction& Fraction::operator/= (const Fraction other) {
    if (other.numer == 0) {
        printf("Error: Unable to Divide by 0\nAssign the Fraction to 0 / 1\n");

        *this = Fraction();
        return *this;
    }

    this->numer = this->numer * other.denom;
    this->denom = this->denom * other.numer;

    return *this;
}

std::istream& operator>>(std::istream& is,const Fraction& frac) {
    is >> frac.numer >> frac.denom;

    return  is;
}
std::ostream& operator<< (std::ostream& os, const Fraction frac) {
    os << frac.numer << '/' << frac.numer;

    return os;
}


