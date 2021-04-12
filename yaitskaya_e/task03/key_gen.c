#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int cre_passwd(const char *user_name);
int buffer_func(const char *user_name);

int main(int argc, char **argv)
{
  int result; // eax
  char *user_name; // esi
  if ( argc > 1 ) {
	user_name = argv[1];
    cre_passwd(user_name);
  }
  else {
	  printf("checkpoint befor else\n"); 
    puts("Specify user name...");
    result = -1;
  }
  return result;
}

int cre_passwd(const char *user_name){
  char v3; // bp
  unsigned int i; // edx
  unsigned int v5; // kr08_4
  char *v6; // edx
  char uname1[128]; // [esp+24h] [ebp-A0h] BYREF

  v3 = buffer_func(user_name);
  memset(uname1, 0, sizeof(uname1));
  for ( i = 0; strlen(user_name) - 1 > i; uname1[i] = user_name[i - 1] )
  {
    uname1[i] = user_name[i + 1];               // load a1 to v8 ?
    ++i;
  }
  v5 = strlen(uname1) + 1;
  if ( (v5 - 1) > 0 )
  {
    v6 = uname1;
    do
    {
      *v6 = (*v6 ^ v3) % 0x19u + 65;
      ++v6;
    }
    while ( v6 != &uname1[v5 - 1] );
  }
  printf("Generated password: ");
  printf(uname1);
  printf("\n");
  return 0;
}


int buffer_func(const char *user_name){
  unsigned int v1; // kr04_4
  char *v2; // eax
  int v3; // edx
  unsigned int v4; // kr08_4
  const char *i; // eax
  char Buffer[128]; // [esp+Ch] [ebp-90h] BYREF

  memset(Buffer, 0, sizeof(Buffer));
  DWORD pcbBuffer; // [esp+10h] [ebp-14h] BYREF
  pcbBuffer = 128;
  
  GetUserNameA(Buffer, &pcbBuffer);
//  printf("GetUserNameA:\t%s\n", Buffer);
  
                     
  v1 = strlen(Buffer) + 1;
  v2 = Buffer;                                  // v2 = buffer[0]
  v3 = 0;
  while ( v2 != &Buffer[v1 - 1] )               // & - address of the last buffer char
    v3 += *v2++;                                // sum buffer chars; v3 = 128?
  v4 = strlen(user_name) + 1;                          // length of a1
  for ( i = user_name; i != &user_name[v4 - 1]; ++i )         // i = a[0], i!=a[last]
    v3 += *i;                                   // buffer chars + a1 chars
  return v3;        
}