#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

void PrintFileOrFolder(filesystem::file_status status) {
    if (status.type() == filesystem::file_type::regular) {
        cout << "Путь указывает на файл"sv << endl;
    }
    else if (status.type() == filesystem::file_type::directory) {
        cout << "Путь указывает на папку"sv << endl;
    }
    else {
        cout << "Путь указывает другой объект"sv << endl;
    }
}

/*
Элемент папки dir_entry имеет тип filesystem::directory_entry,
который помимо самого пути уже содержит в себе закешированный
статус и другую информацию. Чтобы не выполнять лишних обращений
к файловой системе, можно использовать этот статус, изменив
функцию PrintFileOrFolder:
*/

void PrintFileOrFolder(filesystem::path p) {
    error_code err;
    auto status = filesystem::status(p, err);

    if (err) {
        return;
    }

    PrintFileOrFolder(status);
}

int main() {
    setlocale(LC_ALL, "Ru");
    path p = "a"_p / "folder"_p;
    filesystem::create_directories(p);
    filesystem::create_directory(p / "subfolder"_p);
    std::ofstream(p / "file.txt"_p) << "File content"sv;
    //Цикл в функции main тоже нужно заменить:
    for (const auto& dir_entry : filesystem::directory_iterator(p)) {
        PrintFileOrFolder(dir_entry.status());
    }
}
