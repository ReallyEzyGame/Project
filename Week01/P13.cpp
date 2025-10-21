#include <stdio.h>
#include <math.h>

int main()
{
    float edge1, edge2, edge3;

    printf("Input the Lengths of the Triangle: ");
    scanf("%f %f %f", &edge1, &edge2, &edge3);

    double p = (edge1 + edge2 + edge3) / 2.0f;
    double area = sqrt(p * (p - edge1) * (p - edge2) * (p - edge3));

    printf("- Triangle Parimeter: %.2lf\n", p * 2);
    printf("- Triangle Area: %.2lf\n", area);
}