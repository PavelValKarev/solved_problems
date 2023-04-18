#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    setlocale(LC_ALL, "Ru");

    int32_t number_to_serialize = 31415927;
    int32_t read_number = 0;
    {
        ofstream out_file("some_file.txt");
        out_file << number_to_serialize << endl;
    }
    {
        ifstream in_file("some_file.txt");
        in_file >> read_number;
    }
    cout << "Прочитали "sv << read_number << ", ожидали "sv << number_to_serialize
        << (read_number == number_to_serialize ? ". Успех!"sv : ". Ошибка :("sv);
    
}
