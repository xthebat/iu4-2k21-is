#include <stdio.h>
#include <Windows.h>

int main() {
    puts("Put your name, which name > 7 symbols");
    char name[128];
    char serialNumber[128];
    __int16 sum_string = 0;
    //char *serialNumber = "0025_3887_01C4_9F3D.  \r";
    scanf("%s", &name);
    scanf("%s", &serialNumber);

    for(int i = 0; strlen(serialNumber) > i; ++i){
        sum_string += serialNumber[i];
    }
    sum_string = sum_string + ' ' + ' ' + '\r';

    char buffer[128];

    for(int i = 0; strlen(name) > i; i++){
        buffer[i] = (sum_string ^ name[i]) % 25 + 97;
    }

    printf("%s", buffer);
}