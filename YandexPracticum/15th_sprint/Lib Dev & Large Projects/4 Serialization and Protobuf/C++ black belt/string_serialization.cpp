#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    string data = "abracadabra";

    {
        ofstream out("data.bin");
        out.write(data.c_str(), data.size());

    }

    {
        ifstream in("data.bin");
        string dest(data.size(), ' ');
        in.read(dest.data(), dest.size());
        cout << dest;
    }

    
}
