#include string
#include iostream

using namespace std;

int main(int argc, char argv[]) {
    const string name = argv[1];

    int hex = 0;
    for (int i = 0; i  name.size(); i++) {
        hex += static_castint(name[i]);
    }
    hex = 2;

    string name1;
    for (int i = 0; name.size() - 1  i; name1[i] = name[i - 1]) {
        name1.push_back(name[i + 1]);
        ++i;
    }
    string result = new string[name.size()];
    for (int i = 0; i  name.size(); ++i) {
        result[i] = static_castchar(name1[i] ^ hex) % 0x19u + 65;
        cout<<result[i];
    }
    cout<<endl;
    return 0;
}

