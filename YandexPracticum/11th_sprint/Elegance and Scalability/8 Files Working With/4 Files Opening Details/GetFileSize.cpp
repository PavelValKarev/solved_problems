#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// реализуйте эту функцию:
size_t GetFileSize(string file)
{
    ifstream stream(file);
    //Сделайте seekg на конец файла, задав std::ios::end вторым параметром.
    stream.seekg(0, std::ios_base::end);
    //После открытия проверьте, что файл был открыт, конвертировав поток в bool в условии if.
    //Конвертируйте результат к size_t операцией static_cast.
    return static_cast<size_t>(stream.tellg());    
}

int main() {
    ofstream("test.txt") << "123456789"sv;
    assert(GetFileSize("test.txt"s) == 9);

    ofstream test2("test2.txt"s);
    test2.seekp(1000);
    test2 << "abc"sv;
    test2.flush();

    assert(GetFileSize("test2.txt"s) == 1003);
    assert(GetFileSize("a file not exists"s) == string::npos);
}
