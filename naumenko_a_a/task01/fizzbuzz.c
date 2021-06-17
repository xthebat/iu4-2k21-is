#include <stdio.h>

int main()
{
	int count = 0;
	printf("Введите число");
	scanf("%d", &count);
	int i = 1;
	while (i <= count) 
	{
		if (i % 3 == 0) printf("Fizz");
		if (i % 5 == 0) printf("Buzz");
		if (!(i % 3 == 0) && !(i % 5 == 0)) printf("%d", i);
		if (i == count) printf(".");
		else printf(", ");
		i++;
	}
	return 0;
}