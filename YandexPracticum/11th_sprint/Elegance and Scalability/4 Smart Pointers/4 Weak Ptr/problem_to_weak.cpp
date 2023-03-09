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

    Person* person = nullptr;
};

// ----- Начало изменений ----
void PrintApartmentInfo(const Apartment& apartment) {
    if (apartment.person) {
        cout << apartment.person->name << " is living in the apartment" << endl;
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
        apartment->person = person.get();
        cout << "----"sv << endl;

        
    }
    PrintApartmentInfo(*apartment);
}
// ----- Конец изменений ---- 
