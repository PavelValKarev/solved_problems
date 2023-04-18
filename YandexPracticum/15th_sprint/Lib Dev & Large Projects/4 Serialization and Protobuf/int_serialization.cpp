#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    setlocale(LC_ALL, "Ru");

    int32_t number_to_serialize = 31415927;
    int32_t read_number = 0;
    {
        ofstream out_file("some_file.bin");
        out_file.write(reinterpret_cast<const char*>(&number_to_serialize), sizeof(number_to_serialize));
    }
    {
        ifstream in_file("some_file.bin");
        in_file.read(reinterpret_cast<char*>(&read_number), sizeof(read_number));
    }
    cout << "Прочитали "sv << read_number << ", ожидали "sv << number_to_serialize
        << (read_number == number_to_serialize ? ". Успех!"sv : ". Ошибка :("sv);
    
}
