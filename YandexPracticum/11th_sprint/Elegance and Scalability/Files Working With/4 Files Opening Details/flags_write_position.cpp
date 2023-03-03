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
        //запись в начало файла (перезаписывает текст поверх старого)
        fstream fout("telefon.txt", ios::in | ios::out);
        //добавляем позицию записи
        fout.seekp(72);
        fout << "- Слон."s << endl;
        //tellp() сообщает позицию: 
        cout << "Writing at pos: "s << fout.tellp() << endl;
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
