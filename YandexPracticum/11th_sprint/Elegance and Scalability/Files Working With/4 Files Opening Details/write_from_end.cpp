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
        //позицию записи отсчитываем с конца смещаясь на 10 символов (подбирал)
        fout.seekp(-10, ios::end);
        fout << "на линии?"sv << endl << "- Слон."sv << endl;
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
