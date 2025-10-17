#include "lib.h"

Fraction::Fraction() : numerator(0), denominator(1) {}
Fraction::Fraction(const int numer) : numerator(numer), denominator(1) {}
Fraction::Fraction(std::string str)
{
    if (str.empty())
    {
        numerator = 0;
        denominator = 1;
    }

    int idx = 0;
    // Find char '/'
    while (idx < str.size() && str[idx++] != '/')
        ;

    int numer = strToInteger(str.substr(0, idx - 1));
    int denom = strToInteger(str.substr(idx));

    numerator = numer;
    if (denom == 0)
        denominator = 1;
    else
        denominator = denom;
}
Fraction::Fraction(const Fraction &other)
{
    numerator = other.numerator;
    denominator = other.denominator;
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

    numerator = numer;
    denominator = denom;
}
void Fraction::output()
{
    printf("%d/%d", numerator, denominator);
}
Fraction &Fraction::getNum()
{
    return *this;
}
void Fraction::setNum(const Fraction other)
{
    numerator = other.numerator;
    denominator = other.denominator;
}
int Fraction::getDenom()
{
    return denominator;
}
void Fraction::setDenom(const int denom)
{
    if (denom == 0)
    {
        printf("Error: Denominator cannot be 0\n");
    }
    else
        denominator = denom;
}
Fraction Fraction::reduce()
{
    Fraction frac(*this);

    bool numerSign = frac.numerator < 0;   // Numerator's Sign
    bool denomSign = frac.denominator < 0; // Denominator's Sign

    frac.numerator = abs(numerator);
    frac.denominator = abs(denominator);

    int min = (frac.numerator > frac.denominator) ? frac.denominator : frac.numerator;

    for (int i = min; i > 1; --i)
    {
        if (frac.numerator % i == 0 && frac.denominator % i == 0)
        {
            frac.numerator /= i;
            frac.denominator /= i;
            ++i;
        }
    }

    if (numerSign xor denomSign)
        frac.numerator *= -1;

    return frac;
}
Fraction Fraction::add(const Fraction other)
{
    Fraction frac;
    frac.numerator = numerator * other.denominator + denominator * other.numerator;
    frac.denominator = denominator * other.denominator;

    return frac;
}
Fraction Fraction::inverse()
{
    if (numerator == 0)
    {
        printf("Error: Cannot Divide by 0\nReturn the same fraction\n");

        return *this;
    }
    // Swap numerator & denominator
    Fraction frac;
    frac.numerator = denominator;
    frac.denominator = numerator;

    bool numerSign = frac.numerator < 0;   // Numerator's Sign
    bool denomSign = frac.denominator < 0; // Denominator's Sign

    frac.numerator = abs(frac.numerator);
    frac.denominator = abs(frac.denominator);

    if (numerSign xor denomSign)
        frac.numerator *= -1;

    return frac;
}
int Fraction::compare(const Fraction other)
{
    int delta1 = numerator * abs(other.denominator);
    int delta2 = other.numerator * abs(denominator);

    if (delta1 < delta2)
        return -1;
    else if (delta1 > delta2)
        return 1;
    else
        return 0;
}

bool isDigit(const char ch)
{
    return '0' <= ch && ch <= '9';
}
int strToInteger(std::string str)
{
    // nullptr case
    if (str.empty())
        return 0;

    bool negative;
    int result = 0, idx = 0;

    if (str[idx] == '-')
    {
        negative = true;
        idx++;
    }
    else if (str[idx] == '+')
    {
        idx++;
    }

    for (; idx < str.size() && str[idx] != 0; ++idx)
    {
        if (!isDigit(str[idx]))
        {
            printf("Error: Unexpected token %c at %d\n", str[idx], idx);
            printf("Return 0\n");

            return 0;
        }
        result = result * 10 + (str[idx] - '0');
    }

    if (negative)
        result *= -1;
    return result;
}