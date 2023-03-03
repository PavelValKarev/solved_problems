#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

//параметры: поток, путь, статус, отступ при печати)
void PrintTree(ostream& dst, const path& p, const filesystem::file_status& status, int offset)
{
    //filesystem::file_status status = filesystem::status(p);
    //std::cout << "checking " + p.filename().string() << std::endl;
    //если статус: папка 
    if (status.type() == filesystem::file_type::directory)
    {
        std::vector<filesystem::directory_entry> files;
        //Элемент папки dir_entry имеет тип filesystem::directory_entry, который помимо самого
        //пути уже содержит в себе закешированный статус и другую информацию. 
        for (const auto& dir_entry : filesystem::directory_iterator(p)) {
            //std::cout << "it has " + dir_entry.path().filename().string() << std::endl;
            //наполняем созданный выше контейнер
            files.push_back(dir_entry);
        }
        //сортируем лексикографически
        //через лямбду. Лямбда работает с объектами directory_entry
        std::sort(files.begin(), files.end(), [](filesystem::directory_entry a, filesystem::directory_entry b) {

            std::string aName = a.path().filename().string();
            std::string bName = b.path().filename().string();
            return std::lexicographical_compare(bName.begin(), bName.end(), aName.begin(), aName.end());

            });
        //выводим с отступом
        dst << string(offset, ' ') << p.filename().string() << std::endl;
        for (const auto& dir_entry : files) {
            PrintTree(dst, dir_entry.path(), dir_entry.status(), offset + 2);
        }
    }
    //если статус::файл
    else
    {
        //std::cout << "printing final " + p.filename().string() << " offset is " << offset << std::endl;
        dst << string(offset, ' ') << p.filename().string() << std::endl;
    }


}

// напишите эту функцию
void PrintTree(ostream& dst, const path& p)
{
    filesystem::file_status status = filesystem::status(p);
    PrintTree(dst, p, status, 0);
}

int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"sv
    );
}
