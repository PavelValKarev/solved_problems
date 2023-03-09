#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int main(int argc, const char** argv) {
    
    setlocale(LC_ALL, "Ru");
    
    // 1
    {
        fstream fout("telefon.txt", ios::out);
        fout << "У меня зазвонил телефон."sv << endl;
        fout << "- Кто говорит?"sv << endl;
    }

    // 2
    {
        //комбинация флагов для записи в конец файла
        fstream fout("telefon.txt", ios::out | ios::app);
        fout << "- Слон."sv << endl;
    }

    // 3
    {
        fstream fin("telefon.txt", ios::in);
        string str;
        while (getline(fin, str)) {
            cout << str << endl;
        }
    }
}
