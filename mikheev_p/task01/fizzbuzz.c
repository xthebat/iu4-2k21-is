#include<stdio.h>
void fizzBuzz(int num){
    int number = num;
    if(number%3 == 0 && number%5 == 0){
        printf("Fizz Buzz\n");
    }
    else if(number % 5 == 0){
        printf("Buzz\n");
    }
    else if(number % 3 == 0)
        printf("Fizz\n");
    else
        printf("%d\n", number);
}

int main(void){
    for(int i=1; i <= 100; i++){
        fizzBuzz(i);
    }
}