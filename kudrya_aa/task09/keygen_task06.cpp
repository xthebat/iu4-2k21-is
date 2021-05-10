#include <iostream>
#include <string>
using namespace std;

void get_serial_number(char serial_number[128]);

int main(int argc, char** argv)
{
	const char* username = argv[1];
	string str;
	uint16_t temp = 0;
	char serial_number[128];
	get_serial_number(serial_number);

	for (int i = 0; strlen(serial_number) > i; ++i) 
		temp += serial_number[i];
	for (int i = 0; i < 8; i++)
		str.push_back((temp ^ username[i]) % 25 + 97);

	cout << "Password: " << str << endl;
   
}

void get_serial_number (char serial_number[128])
{
	FILE* file; 
	char Buffer[1024]; 
	file = _popen("wmic path win32_physicalmedia get SerialNumber", "r");
	if (!file)
		exit(1);
	fgets(Buffer, 1024, file);
	memset(Buffer, 0, sizeof(Buffer));
	fgets(Buffer, 1024, file);
	strcpy_s(serial_number,128, Buffer);
	serial_number[strlen(serial_number) - 1] = 0;
	_pclose(file);
}
