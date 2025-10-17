#include "ex32.h"

int Fraction::count = 0;

// Convere a string of number to Integer
// this function can only handle integer( both positive & negative)
int toInteger(const std::string str) {
    int num = 0, idx = 0;
    bool negative = (str[idx] == '-') ? true : false;

    if (negative) idx++;


    while (idx < str.size()) {
        num = num * 10 + (str[idx++] - '0');
    }

    return (negative) ? - num : num;
}








Fraction::Fraction(): numer(0), denom(1) { countObject();}
Fraction::Fraction(const int num, const int den) {
    if (den == 0) {
        printf("Error: Denominator cannot be 0\n");
        printf("Default Denominator to 1\n");

        denom = 1;
    }
    else denom = den;

    numer = num;

    countObject();
}
Fraction::Fraction(const int num) : numer(num), denom(1) { countObject();}
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

    countObject();
} 
Fraction::Fraction(const Fraction& other) {
    numer = other.numer;
    denom = other.denom;

    countObject();
}
void Fraction::countObject() {
    ++count;
}
void Fraction::input()
{
    int numer, denom;
    printf("Input Numerator & Denominator: ");
    scanf("%d %d", &numer, &denom);

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
int Fraction::getDenom()
{
    return denom;
}
int Fraction::getNumberOfObject() {
    return count;
}
void Fraction::setNum(const Fraction other)
{
    numer = other.numer;
    denom = other.denom;
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
Fraction Fraction::add(const Fraction other) {
    Fraction number;
    number.numer = numer *  other.denom + denom * other.numer;
    number.denom = denom * other.numer;

    return number;
}
Fraction Fraction::inverse() {
    // Swap numerator & denominator
    int temp = numer;
    numer = denom;
    denom = numer;

    return *this;
}
int Fraction::compare(const Fraction other)  {
    int delta1 = numer * abs(other.denom);
    int delta2 = other.numer * abs(denom);
    
    if (delta1 < delta2)
        return -1;
    else if (delta1 > delta2)
        return 1;
    else return 0;
}


int main() {
    Fraction frac;

    printf("\n%d\n", frac.getNumberOfObject());
    
}