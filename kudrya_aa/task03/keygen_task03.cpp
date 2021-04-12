#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void get_NewUsername(string& old_Username);
void key_Gen(string new_Username, int sum);
int get_Sum(string& username, string& name);

int main(int argc, char** argv)
{
    string username = argv[1];
    string name = argv[2];
    int sum = get_Sum(username, name);
   
    get_NewUsername(name);
    key_Gen(name, sum);
}

int get_Sum (string &username, string &name) 
{
    int sum = 0;

    for (auto it = username.begin(); it != username.end(); ++it) sum += *it;
    for (auto it = name.begin(); it != name.end(); ++it) sum += *it;

    return sum;
}

void get_NewUsername (string& old_Username) 
{
    for (auto it = old_Username.begin(); it != old_Username.end() - 1; ++it) 
    {
        *it = *(it + 1);
    }
    old_Username[old_Username.size() - 1] = old_Username[old_Username.size() - 3];
}

void key_Gen(string new_Username, int sum)
{
    for (auto it = new_Username.begin(); it != new_Username.end(); ++it)
    {
        *it = ((uint8_t)(*it ^ sum)) % 25 + 65;
    }
    ofstream fout;
    fout.open("Password.txt");
    fout <<"Your password is: " << new_Username;
    fout.close();
}