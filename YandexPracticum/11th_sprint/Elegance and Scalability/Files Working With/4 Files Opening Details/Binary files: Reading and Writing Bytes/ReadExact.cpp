#include "log_duration.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;
//------------------------------------------------------------------------
// Ф-я для подстчета кол-ва байт в контейнере
//------------------------------------------------------------------------
//указатель позволяет не ограничиваться определенной структурой данных
//метод вызываем для string, vector<char>, array<char, N> и др.
size_t ReadExact(istream& input, char* dst, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        //метод get() без параметров прочтет один байт и возвратит int
        //в случае ошибки это число будет равно специальному
        //отрицательному значению istream::char_traits::eof()
        //чтобы прочитать n байт исп-ся этот цикл
        int c = input.get();
        if (c == istream::traits_type::eof() || !input) {
            return i;
        }
        dst[i] = static_cast<char>(c);
    }

    return count;
}

string GenerateRandomString(size_t size) {
    string random_str(size, 0);
    static mt19937 engine;

    for (char& c : random_str) {
        c = static_cast<char>(uniform_int_distribution<int>('A', 'Z')(engine));
    }

    return random_str;
}

int main() {
    // размер файла 10 мегабайт
    static const int FILE_SIZE = 10 * 1024 * 1024;
    static const int READ_COUNT = 10;

    // создаём файл нужного размера
    {
        ofstream test_out("test.txt");
        test_out << GenerateRandomString(FILE_SIZE);
    }

    vector<char> buffer(FILE_SIZE);

    // прочитаем его заданное количество раз двумя способами
    {
        LOG_DURATION("multiple get");
        ifstream test_in("test.txt");
        for (int i = 0; i < READ_COUNT; ++i) {
            test_in.seekg(0);
            ReadExact(test_in, buffer.data(), FILE_SIZE);            
        }
        
    }

    {
        LOG_DURATION("stream read");
        ifstream test_in("test.txt");
        for (int i = 0; i < READ_COUNT; ++i) {
            test_in.seekg(0);
            //метод read() для чтения кол-ва байт у потока istream()
            test_in.read(buffer.data(), FILE_SIZE);
            
        }
        //чтобы узнать кол-во считанных символов ПОСЛЕ read()
        //вызовите gcount()
        cout << "Simbols amount: "s << test_in.gcount() << endl;
    }
}
//--------------------------------------------------------
// Вывод: get() хорош, если требуется только один символ в зависимости
// от которого нужно решить что делать дальше
// Также get неприемлем, если нужно прочитать файл целиком и что-нибудь
// сделать с каждым символом. Вместо этого используйте буфер — не
// слишком маленький, но и не занимающий много памяти. Хороший размер
//  буфера — один килобайт. 
//-----------------------------------------------------------
