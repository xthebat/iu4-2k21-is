#include <stdio.h>

int main(void)
{
	int number = 0;
    int i;
	printf("Enter a number: ");
	scanf_s("%d", &number);
	
	for(i=0;i<=number;i++) 
	{
        if (i % 3 == 0 && i % 5 == 0) printf("FizzBuzz");
        continue;
        if (i % 3 == 0) printf("Fizz");
        continue;
		if (i % 5 == 0) printf("Buzz");
		continue;
		if (i == number) printf(".");
		else printf("%d ",i);
		
	}
	return 0;
}