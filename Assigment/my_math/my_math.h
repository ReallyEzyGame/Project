#define PI 3.14159
#define PRECISION 15

// This type of number is based on string to contain big number
struct BigInt;


// get the value x power of n
double pow(double,int);
// get the factorial of value n
unsigned long long fac(int);
// these function of trigeometry using radiant angle
// 0 <= radinant <= 2 * PI, if the value is higher or smaller then it will be reduce to satisfy the condition
double sin(double);
double cos(double);
double tan(double);
double cot(double);

// get the x value of n  root
double nInt_root(double, int);
double nFloat_root(double,double);