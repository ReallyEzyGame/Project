#include "my_math.h"

// using the binary power to archive faster calculation
double pow(double x, int n) {
    double result = 1;

    while (n > 0) {
        if (n % 2 == 1)
            result *= x;
        result *= result;
        n /= 2;
    }
    return result;
}

unsigned long long fac(int n) {
    unsigned long long result = 1;
    while (n > 1) {
        result *= n;
        n--;
    }
    return result;
}


double sin(double rad) {
    double result = 0.f;

    for (int i = 0; i <= PRECISION; ++i) {
        result += ((i % 2) ? -1 : 1) * pow(rad, 2 * i + 1) / fac(2 * i + 1);
    }

    return result;
}
double cos(double rad) {
    double result = 0.f;

    for (int i = 0; i <= PRECISION; ++i) {
        result += ((i % 2) ? -1 : 1) * pow(rad, 2 * i) / fac(2 * i);
    }

    return result;
}
double tan(double rad) {
    double val1 =  sin(rad);
    double val2 = cos(rad);

    if (val2 == 0)
        return 0;

    return val1 / val2;
}
double cotan(double rad) {
    double val1 =  sin(rad);
    double val2 = cos(rad);

    if (val2 == 0)
        return 0;

    return val2 / val1;
}


double n_int_root(double x, int n) {
    double y = x;
    double power;

    for (int i = 0; i <= PRECISION; ++i) {
        power = pow(y, n - 1);
        y = y - (power * y - x) / (n * power); 
    }

    return power;
}
double n_float_root(double x, double real) {
    int exp_limit = 20;         // the max value of a exponent can get

    // Calculate the integer part first
    double y = n_int_root(x, (int) real);
    real = real - (int)(real);  // get the decimal part

    for (int i = 0; i <= PRECISION && real > 0; ++i) {
        real *= 10;
        y *= n_int_root(x, (int) real);
        real -= (int) real;
    }

    return y;
}