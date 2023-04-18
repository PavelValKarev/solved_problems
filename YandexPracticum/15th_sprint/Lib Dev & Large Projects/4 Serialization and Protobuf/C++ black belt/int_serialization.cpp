#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    int value = 5036843;

    {
        ofstream out("data.bin");
        //сохраним число в выходной поток
        out.write(reinterpret_cast<char*>(&value), sizeof(value));

    }

    //считаем наше число
    { 
        value = 1234;
        ifstream in("data.bin");
        in.read(reinterpret_cast<char*>(&value), sizeof(value));
        cout << value;
    }

    
}
