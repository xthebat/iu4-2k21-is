#include <stdio.h>
#include <Windows.h>

int main() {
    char name[128];
    scanf("%s", name);

    int len_name = strlen(name);
    int sum_hex = 0;
    for (int i=0; i < len_name; i++){
       sum_hex += name[i];
    }
    sum_hex = sum_hex*2;

    char v8[len_name];
    memset(v8, 0, len_name);
    for (int i=0; strlen(name)-1 > i; v8[i] = name[i-1]){
       v8[i] = name [i + 1];
       ++i;
    }
    char result[128];
    for(int i=0; i < len_name; ++i){
       result[i] = (char)(v8[i] ^ sum_hex) % 0x19u + 65;
       printf("%c", result[i]);
    }
    printf("\n");
}

