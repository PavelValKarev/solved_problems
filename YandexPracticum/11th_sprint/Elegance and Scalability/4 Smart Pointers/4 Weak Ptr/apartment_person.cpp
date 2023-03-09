#include <memory>
#include <iostream>
#include <string>

using namespace std;

struct Apartment;

struct Person {
    explicit Person(string name)
        : name(move(name))  //
    {
        cout << "Person "sv << this->name << " has been created"sv << endl;
    }
    ~Person() {
        cout << "Person "sv << name << " has died"sv << endl;
    }

    string name;
    shared_ptr<Apartment> apartment;
};

struct Apartment {
    Apartment() {
        cout << "The apartment has been created"sv << endl;
    }
    ~Apartment() {
        cout << "The apartment has been destroyed"sv << endl;
    }

    shared_ptr<Person> person;
};

//Создадим человека и квартиру и свяжем их друг с другом:
int main() {
    auto apartment = make_shared<Apartment>();
    auto person = make_shared<Person>("Ivan"s);
    person->apartment = apartment;
    apartment->person = person;
}
//Запустив программу, столкнёмся с утечкой памяти: ни у
//человека, ни у квартиры не был вызван деструктор.

/*
Суть проблемы в том, что между person и apartment возникла циклическая ссылка.
Циклическая ссылка — ситуация, при которой в программе появляется циклическая
последовательность владеющих ссылок. В данном случае:
объект person владеет объектом apartment, не давая ему уничтожиться;
объект apartment владеет объектом person, также не давая ему уничтожиться.
*/
