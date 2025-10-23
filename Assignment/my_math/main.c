#include <stdio.h>

#define PI 3.14159
#define PRECISION 15

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



int main(void) {
    printf("cos(e): %lf\n", cos(2.718281828));
}