#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>
#include <iostream>

using namespace std;
using filesystem::path;

int main()
{
    //Тут вы видите второй параметр при конструировании пути из string.По
    //умолчанию он равен path::generic_format::auto_format.Это значение
    //подразумевает, что компилятор постарается универсальным образом
    //интерпретировать путь.
    path p = path("a/folder/and/../a/file.txt"s, path::generic_format);

    cout << "p.string():                      "sv << p.string() << endl;
    //Под Windows путь в native-формате иногда содержит оба вида слешей,
    //но предпочтительнее обратный. Можно явно заменить в переменной типа
    //path все слеши на предпочтительные методом make_preferred:
    p.make_preferred();
    cout << "p.string() после make_preferred: "sv << p.string() << endl;
    //Формат generic одинаковый на всех операционных системах. Он определяет
    //папки прямым слешем. Чтобы получить generic-представление, вызовите
    //метод generic_string. 
    cout << "p.generic_string():              "sv << p.generic_string() << endl;
}
