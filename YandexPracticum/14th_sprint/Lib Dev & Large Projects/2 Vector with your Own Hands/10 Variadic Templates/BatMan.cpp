#include <string>
#include <iostream>

using namespace std;

/*
Распаковать можно не только пакет параметров функции, но и пакет параметров
шаблона. Используем это, чтобы создать химер — существ, обладающих свойствами
нескольких организмов:
*/

struct Man {
    void SayHello() { cout << "Hi!"sv << endl; }
};
struct Bat {
    void Fly() { cout << "I'm flying!!!"sv << endl; }
};
struct Spider {
    void Weave() { cout << "I'm weaving a web"sv << endl; }
};

// Химера, наследуется от переданных ей базовых классов
template <typename... Bases>
class Chimera : public Bases... {};

int main() {
    Chimera<Bat, Man> batman;
    batman.SayHello();
    batman.Fly();

    Chimera<Spider, Man> spiderman;
    spiderman.Weave();
    spiderman.SayHello();
}

/*
Этот искусственный пример с наследованием иллюстрирует идею,
на которой основываются полезные стандартные классы, например std::tuple.
*/
