#include <stdio.h>

int main() {
    char username[128];
    scanf("%s", username);

    int len_username = strlen(username);
    int sum_hex = 0;
    for (int i=0; i < len_username; i++){
       sum_hex += username[i];
    }
    sum_hex = sum_hex*2;

    char v8[len_username];
    memset(v8, 0, len_username);
    for (int i=0; strlen(username)-1 > i; v8[i] = name[i-1]){
       v8[i] = username [i + 1];
       ++i;
    }
    char result[128];
    for(int i=0; i < len_username; ++i){
       result[i] = (char)(v8[i] ^ sum_hex) % 0x19u + 65;
       printf("%c", result[i]);
    }
    printf("\n");
}

