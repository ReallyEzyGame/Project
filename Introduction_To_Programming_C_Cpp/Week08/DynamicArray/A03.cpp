#include <string.h>
#include <stdio.h>

bool isPolidrome(char *str)
{
    int len = strlen(str);
    char *front = str;
    char *back = str + len - 1;

    while (front < back)
    {
        if (*front != *back)
        {
            return 0;
        }

        front++;
        back--;
    }

    return 1;
}

int main()
{
    char *str1 = "12345654321";
    char *str2 = "this is not a palidrome str";

    if (isPolidrome(str1))
    {
        printf("str '%s' is a polidrome\n", str1);
    }
    else {
        printf("str '%s' is not a polidome\n", str1);
    }


    if (isPolidrome(str2))
    {
        printf("str '%s' is a polidrome\n", str2);
    }
    else {
        printf("str '%s' is not a polidrome\n", str2);
    }
}