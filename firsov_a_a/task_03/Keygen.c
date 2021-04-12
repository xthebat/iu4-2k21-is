#pragma warning(disable:4996)

#include <stdio.h>
#include <Windows.h>
int main() {
    char name[] = "Ankare";
    int len_name = strlen(name);
    int binary_sum = 0;
    char password[128];
    memset(password, 0, sizeof(password));
    char result[20];
    for (int i = 0; i < len_name; i++) 
        {
        binary_sum += name[i];
    }
    binary_sum = binary_sum * 2;

    for (int i = 0; strlen(name) - 1 > i; password[i] = name[i - 1]) 
        {
        password[i] = name[i + 1];
        ++i;
    }
    for (int i = 0; i < len_name && result != '\0'; i++) 
        {
        result[i] = (unsigned __int8)(password[i] ^ binary_sum) % 0x19u + 'A';
    }
    printf("%s", result);
}