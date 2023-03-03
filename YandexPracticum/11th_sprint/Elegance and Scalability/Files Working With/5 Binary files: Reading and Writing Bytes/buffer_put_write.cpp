//Аналоги get и read для записи — методы put и write.
//не следует использовать put для записи многих символов подряд.
//Напишем собственную версию утилиты cp, которая копирует файлы. 
//При этом применим буфер:



#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

//параметры main() рассматриваются в задании по 
//компрессору и декомпрессору
int main(int argc, const char** argv) {
    setlocale(LC_ALL, "Ru");
    // при неверных аргументах выводим ошибку и выходим с кодом
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <in file> <out file>"sv << endl;
        return 1;
    }

    ifstream in_file(argv[1], ios::in | ios::binary);
    if (!in_file) {
        cerr << "Can't open input file"sv << endl;
        return 2;
    }

    ofstream out_file(argv[2], ios::out | ios::binary);
    if (!out_file) {
        cerr << "Can't open output file"sv << endl;
        return 2;
    }
    //-----------------------------------------------
    // размер буфера один килобайт
    static const int BUFF_SIZE = 1024;
    std::array<char, BUFF_SIZE> buffer;

    do {
        in_file.read(buffer.data(), BUFF_SIZE);
        out_file.write(buffer.data(), in_file.gcount());
    } while (in_file);
    //-----------------------------------------------
}
