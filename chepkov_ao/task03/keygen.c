#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "winbase.h"

void main(int argc, char* argv[]) {

	char *sysname = (char*)malloc(sizeof(char) * 128);
	DWORD dwBuffer = strlen(sysname);

	int tries_to_get_sysname = 0;
	int sysname_len;

	do {
		GetUserNameA(sysname, &dwBuffer);
		sysname_len = strlen(sysname);
		tries_to_get_sysname++;
	} while (( *sysname < '0' || (*sysname > '9'
			&& *sysname < 'A') || (*sysname > 'Z'
			&& *sysname < 'a') || *sysname > 'z' 
			|| *(sysname + 1) < '0' || (*(sysname + 1) > '9'
			&& *(sysname + 1) < 'A') || (*(sysname + 1) > 'Z'
			&& *(sysname + 1) < 'a') || *(sysname + 1) > 'z'
			|| *(sysname + 2) < '0' || (*(sysname + 2) > '9'
			&& *(sysname + 2) < 'A') || (*(sysname + 2) > 'Z'
			&& *(sysname + 2) < 'a') || *(sysname + 2) > 'z'
			|| sysname_len < 3) && tries_to_get_sysname < 64); 

	if (tries_to_get_sysname == 64) {
		printf("Something is not good with your sysname.\n");
		return;
	}

	char *sysname_ptr = sysname;
	int name_char_sum = 0;
	
	while (sysname_ptr != sysname + sysname_len)
		name_char_sum = name_char_sum + *(sysname_ptr++);
	
	char *username;
	if (argc > 1)
		username = argv[1];
	else 
		username = sysname;
	int username_len = strlen(username);
	char *username_ptr = username;
	
	while (username_ptr != username + username_len)
		name_char_sum = name_char_sum + *(username_ptr++);
	
	//-------------------------------------------------------------
	
	if (sysname_len > username_len) {
		printf ("Your username should be longer or equal to sysname to generate correct password.\n");
		return;
	}
		
	char *username_distorted = (char*)calloc(128, sizeof(char));

	for (int counter = 0; counter < (username_len - 1); *(username_distorted + counter) = *(username + counter - 1)) {
		*(username_distorted + counter) = *(username + counter + 1);
		counter++;
		}
		
	if ((username_len - 3) < 0)
		printf ("Your username is too short! It should be at least 3 letters.\n");
	else {
		char *temp_distorted = username_distorted;
		
		do {
			*temp_distorted = (char)(*temp_distorted ^ name_char_sum) % 25 + 65;
			temp_distorted++;
		} while (temp_distorted != (username_distorted + username_len));
		
		for (int counter = 0; counter < username_len; counter++)
			if (*(username_distorted + counter) < 'A' || *(username_distorted + counter) > 'z') {
				printf("Please, try any other username, or leave this argument empty.\n");
				return;
			}

		//printf("Tries to get sysname: %d\n", tries_to_get_sysname);
		//printf("Your sysname: %s\n", sysname);
		//printf("Your sysname length: %d\n", sysname_len);
		printf("Your username: %s\n", username);
		printf("Your password: %s\n", username_distorted);
	}
	
    return;
}
		