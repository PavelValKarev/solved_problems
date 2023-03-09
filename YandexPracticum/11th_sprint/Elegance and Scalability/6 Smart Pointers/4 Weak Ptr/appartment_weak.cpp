#include <memory>
#include <iostream>
#include <string>


/*
Рассмотренная ранее проблема циклических ссылок может быть безопасно решена
с использованием weak_ptr.  Для этого одну из ссылок, образующих цикл, нужно
сделать слабой.
Объявив внутри Apartment слабую ссылку на Person, решим как проблему с 
утечкой памяти, так и проблему висячих ссылок:
*/

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

    // Ссылка на Person автоматически обнулится, когда Person будет удалён
    weak_ptr<Person> person;
};


void PrintApartmentInfo(const Apartment& apartment) {
    if (const auto person = apartment.person.lock()) {
        cout << person->name << " is living in the apartment" << endl;
    }
    else {
        cout << "The apartment is empty"sv << endl;
    }
}

int main() {
    auto apartment = make_shared<Apartment>();
    {
        auto person = make_shared<Person>("Ivan"s);
        person->apartment = apartment;
        apartment->person = person;
        cout << "----"sv << endl;
    }
    PrintApartmentInfo(*apartment);
}
