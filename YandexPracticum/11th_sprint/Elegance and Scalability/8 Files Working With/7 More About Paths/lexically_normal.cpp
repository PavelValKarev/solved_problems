#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>
#include <iostream>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

//Нормализация
//Пути, содержащие элементы папки., папки ..или несколько слешей подряд,
//легко упростить.Это делается методом lexically_normal :
//Полученный путь называется нормальным.

int main()
{
    setlocale(LC_ALL, "Ru");

    path p = "a"_p / "folder"_p / "and"_p / ".."_p / "a"_p / "file.txt"_p;

    cout << "Исходный вид: "sv << p.string() << endl;
    p = p.lexically_normal();
    cout << "После lexically_normal(): "sv << p.string() << endl;
}
