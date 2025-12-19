#include <stdio.h>

int find_mode(const int *values, const int *freq, const int N)
{
    int idx = 0;

    int i = 1;
    while (i < N)
    {
        if (*(freq + i) >= *(freq + idx))
        {
            idx = i;
        }
        ++i;
    }

    return *(freq + idx) > 1 ? idx : -1;
}

int main()
{
    int value[6] = {1,2,3,4,5,6};
    int frequen[6] = {10,20,30,40,50,60};

    for (int i = 0 ; i < 6; ++i) {
        printf("%d : %d\n",value[i], frequen[i]);
    }

    printf("The mode of the value is: %d", value[find_mode(value,frequen,6)]);
}