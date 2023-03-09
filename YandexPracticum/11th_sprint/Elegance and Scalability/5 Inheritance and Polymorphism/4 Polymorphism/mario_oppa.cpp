#include <iostream>

using namespace std;

class Person {
public:
    Person(const string& name, int age)
        : name_(name)
        , age_(age) {
    }

    int GetAge() const { return age_; }
    const string& GetName() const { return name_; }
    
    // Реализация виртуального метода может быть переопределена в классах-наследниках
    virtual void Dance() const {
        cout << name_ << " is dancing"s << endl;
    }

private:
    string name_;
    int age_;
};

enum class WorkerSpeciality { BLACKSMITH, CARPENTER, WOOD_CHOPPER, ENGINEER, PLUMBER };

class Worker : public Person {
public:
    Worker(const string& name, int age, WorkerSpeciality speciality)
        : Person(name, age)
        , speciality_(speciality) {
    }
    void Work() {
        cout << GetName() << " is working"s << endl;
    }
    // Метод Dance переопределяет (override) реализацию базового класса
    void Dance() const override {
        // Сначала вызываем метод Dance родительского класса
        Person::Dance();
        // Добавляем дополнительное поведение
        cout << "Oppa!"s << endl;
    }

private:
    WorkerSpeciality speciality_;
};

void VisitNightClub(const Person& person) {
    if (person.GetAge() >= 18) {
        person.Dance();
    }
    else {
        cout << person.GetName() << " is too young to visit night clubs"s << endl;
    }
}

int main() {
    Person person("Ivan Ivanov"s, 30);
    VisitNightClub(person);

    Worker worker("Mario"s, 40, WorkerSpeciality::PLUMBER);
    VisitNightClub(worker);
}
