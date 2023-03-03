#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    {
        setlocale(LC_ALL, "Ru");
        
        //----------------------------------
        //чтение из файла
        //при создании потока в конструктор нужно передать имя файла
        ifstream in_file("test.txt"s);
        int x;
        if (in_file >> x) {
            cout << "Из файла прочитано число "s << x << endl;
        }
    }

    //создание файла
    {
        ofstream out_file("test.txt"s);
        out_file << 100 << 500 << endl;
    }
}
