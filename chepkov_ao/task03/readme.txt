/*


		Пояснения к коду keygen.c:


*/

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
		GetUserNameA(sysname, &dwBuffer); 	/*Данная функция из winbase.h получает имя пользователя ПК.
											По умолчанию, если не указан первый аргумент, keygen использует
											это имя как имя пользователя в программе. ИСправить это можно,
											введя первый аргумент.
											
											Так вышло, что у меня в 90% случаев с первого раза эта функция
											работает некорректно, выдавая какие-то непонятные ASCII символы
											вместо имени, так что я ввёл проверку while чтобы убедиться,
											что хотя бы три первых символа имени - это буквы или цифры.*/
											
		sysname_len = strlen(sysname);		//Длина имени пользователя ПК.
		tries_to_get_sysname++;				//Количество попыток получить имя.
	} while (( *sysname < '.' || (*sysname > '9'
			&& *sysname < 'A') || (*sysname > 'Z'
			&& *sysname < 'a') || *sysname > 'z' 
			|| *(sysname + 1) < '.' || (*(sysname + 1) > '9'
			&& *(sysname + 1) < 'A') || (*(sysname + 1) > 'Z'
			&& *(sysname + 1) < 'a') || *(sysname + 1) > 'z'
			|| *(sysname + 2) < '.' || (*(sysname + 2) > '9'
			&& *(sysname + 2) < 'A') || (*(sysname + 2) > 'Z'
			&& *(sysname + 2) < 'a') || *(sysname + 2) > 'z'
			|| sysname_len < 3) && tries_to_get_sysname < 64); 

	if (tries_to_get_sysname == 64) {		//Если и с 64 попыток имя не приняло буквенный формат,
		printf("Something is not good with your sysname.\n");
		return;								//Программа завершается ¯\_(ツ)_/¯
	}

	char *sysname_ptr = sysname;			//Указатель на системное имя.
	int name_char_sum = 0;
	
	while (sysname_ptr != sysname + sysname_len)	//Пока указатель не достиг конца строки с именем,
		name_char_sum = name_char_sum + *(sysname_ptr++); /*в name_char_sum записывается сумма значений 
															символов ASCII, из которых оно состоит.*/
	
	char *username;							//Указатель на имя пользователя внутри программы.
	if (argc > 1)							//Если ввели первый аргумент - это становится именем.
		username = argv[1];
	else 
		username = sysname;					//Иначе пользуем имя ПК.
	int username_len = strlen(username);	//Длина имени пользователя.
	char *username_ptr = username;			//Указатель на это имя.
	
	while (username_ptr != username + username_len)
		name_char_sum = name_char_sum + *(username_ptr++); //Такое же сложение символов ASCII для имени.
	
	//-------------------------------------------------------------
	
	if (sysname_len > username_len) {		/*Для упрощения программы имя пользователя должно быть больше 
											или равно длине имени ПК. Я не нашёл место в исходном task05,
											где это проверяется.*/
		printf ("Your username should be longer or equal to sysname to generate correct password.\n");
		return;
	}
		
	char *username_distorted = (char*)calloc(128, sizeof(char));	/*Искажённое дальнейшими преобразованиями имя
																	и есть наш пароль. Выделим для него память.*/

	for (int counter = 0; counter < (username_len - 1); *(username_distorted + counter) = *(username + counter - 1)) {
		*(username_distorted + counter) = *(username + counter + 1);
		counter++;
		}									/*Замысловатый свап порядка символов имени. Первый символ новой строки
											есть второй символ исходной, а последний - повтор предпоследнего.*/
		
	if ((username_len - 3) < 0)				//Пусть имя пользователя будет минимум 3 символа.
		printf ("Your username is too short! It should be at least 3 letters.\n");
	else {
		char *temp_distorted = username_distorted; //Указатель на искажённое имя. Будет перезаписывать его по адресам.
		
		do {
			*temp_distorted = (char)(*temp_distorted ^ name_char_sum) % 25 + 65;
			temp_distorted++;
		} while (temp_distorted != (username_distorted + username_len)); /*Алгоритм шифрации имени:
																		 - Каждый символ строки ксорится с той суммой ASCII;
																		 - Обрезается до одного байта в длину;
																		 - Берётся остаток от деления на 25;
																		 - И к нему прибавляется 65.*/
		
		for (int counter = 0; counter < username_len; counter++)	/*Если в итоговом имени есть какой-то мусор, который нельзя
																	ввести как аргумент в cmd,*/
			if (*(username_distorted + counter) < 'A' || *(username_distorted + counter) > 'z') {
				printf("Please, try any other username, or leave this argument empty.\n"); /*Просим ввести другой пароль.*/
				return;
			}

		//printf("Tries to get sysname: %d\n", tries_to_get_sysname);
		//printf("Your sysname: %s\n", sysname);
		//printf("Your sysname length: %d\n", sysname_len);
		printf("Your username: %s\n", username);					//Выводим в консоль имя пользователя и пароль для входа.
		printf("Your password: %s\n", username_distorted);			/*Потом нужно после ввода этих данных в task05.exe 
																	прописать echo %errorlevel%*/
	}
	
    return;
}
		