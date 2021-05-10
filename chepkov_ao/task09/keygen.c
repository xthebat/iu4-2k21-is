#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

void get_serial(char* serial);

int main(int argc, char* argv[]) {

    char *name = (char*)malloc(sizeof(char) * 128);
	DWORD dwBuffer = 128;

    if (argc > 1)
        name = argv[1];
    else
        GetUserNameA(name, &dwBuffer);

    char sysname[128] = {0};

    strcpy(sysname, name);

    if (strlen(sysname) != 8) {
        printf("\n                   NOTE:\n"); 
        printf("*Your username length should be equal to 8*\n");

        while (strlen(sysname) < 8)
            strcat(sysname, name);
        
        if (strlen(sysname) > 8) {
            int size = strlen(sysname);
            for (int counter = 8; counter < size; counter++)
                sysname[counter] = 0;
        }
    }

    char serial[128] = {0};
    get_serial(serial);

    FILE *file;
    file = fopen("license.txt", "w+");
    printf("\nFile created: license.txt\n");
    fputs((const char*)serial, file);
    fclose(file);
    printf("Serial: %s\n\n", serial);
    
    int serial_summ = 0;

    for(int counter = 0; counter < strlen(serial); counter++){
        serial_summ += serial[counter];
    }

    char password[128] = {0};

    for(int counter = 0; counter < strlen(sysname); counter++){
        password[counter] = (serial_summ ^ sysname[counter]) % 25 + 'a';
    }

    printf("Username: %s\nPassword: %s\n\n", sysname, password);
} 

void get_serial(char* serial) {
  FILE *Stream;
  char Buffer[1024];

  Stream = popen("wmic path win32_physicalmedia get SerialNumber", "r");
  if ( !Stream )
    exit(1);
  fgets(Buffer, 1024, Stream);
  memset(Buffer, 0, sizeof(Buffer));
  fgets(Buffer, 1024, Stream);
  strcpy(serial, Buffer);
  serial[strlen(serial) - 1] = 0;
  pclose(Stream);
  return;
}