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

void PrintFileOrFolder(filesystem::path p) {
    error_code err;
    auto status = filesystem::status(p, err);

    if (err) {
        return;
    }

    if (status.type() == filesystem::file_type::regular) {
        cout << "Путь "sv << p.string() << " указывает на файл"sv << endl;
    }
    else if (status.type() == filesystem::file_type::directory) {
        cout << "Путь "sv << p.string() << " указывает на папку"sv << endl;
    }
    else {
        cout << "Путь "sv << p.string() << " указывает на  другой объект"sv << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    path p = "a"_p / "folder"_p;
    filesystem::create_directories(p);
    filesystem::create_directory(p / "subfolder"_p);
    std::ofstream(p / "file.txt"_p) << "File content"sv;

    for (const auto& dir_entry : filesystem::directory_iterator(p)) {
        PrintFileOrFolder(dir_entry.path());
    }
}
