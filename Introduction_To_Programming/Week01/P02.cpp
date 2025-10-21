#include <stdio.h>

int main()
{
	int num1, num2;

	printf("- Input two integers:");

	scanf("%d %d", &num1, &num2);

	printf("- Sum: %d + %d = %d\n", num1, num2, num1 + num2);

	return 0;
}