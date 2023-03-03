#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

void CreateFile(path p) {
    ofstream file(p);
    if (file) {
        cout << "Файл создан: "sv << p.string() << endl;
    }
    else {
        cout << "Ошибка создания файла: "sv << p.string() << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Ru");

    error_code err;

    path p = "tmp"_p / "a"_p / "folder"_p;

    CreateFile(p / "file.txt"_p);

    filesystem::create_directory(p, err);
    if (err) {
        cout << "Ошибка создания папки через create_directory: "sv << err.message() << endl;
    }
    else {
        cout << "Успешно создана папка через create_directory: "sv << p.string() << endl;
    }

    filesystem::create_directories(p, err);
    if (err) {
        cout << "Ошибка создания папки через create_directories: "sv << err.message() << endl;
    }
    else {
        cout << "Успешно создана папка через create_directories: "sv << p.string() << endl;
    }

    CreateFile(p / "file.txt"_p);

    path p2 = p.parent_path() / "folder2"_p;
    filesystem::create_directory(p2, err);
    if (err) {
        cout << "Ошибка создания папки через create_directory: "sv << err.message() << endl;
    }
    else {
        cout << "Успешно создана папка через create_directory: "sv << p2.string() << endl;
    }

    CreateFile(p2 / "file.txt"_p);
}
