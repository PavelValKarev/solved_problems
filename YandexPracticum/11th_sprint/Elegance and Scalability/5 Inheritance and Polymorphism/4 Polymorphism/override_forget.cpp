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
    
    // Метод Dance умышленно объявлен невиртуальным
    void Dance() const {
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
    // Метод Dance класса Worker замещает собой невиртуальный метод Dance родительского класса
    void Dance() const {
        Person::Dance();
        cout << "Oppa!"s << endl;
    }

private:
    WorkerSpeciality speciality_;
};

/*
Результат вызова невиртуального метода Dance у одного и того же объекта будет зависеть от 
типа ссылки или указателя на объект, которые используются для вызова метода.
*/

void VisitNightClub(const Person& person) {
    if (person.GetAge() >= 18) {
        // Компилятор вызовет метод Person::Dance, так как он не виртуальный
        person.Dance();
    }
    else {
        cout << person.GetName() << " is too young to visit night club"s << endl;
    }
}

/*
Внутри функции VisitNightClub переменная person будет ссылкой
на Person, поэтому будет вызван метод Person::Dance. 
Внутри функции main компилятор знает реальный тип переменной 
worker, поэтому будет вызван метод Worker::Dance:
*/

int main() {
    Worker worker("Mario"s, 40, WorkerSpeciality::PLUMBER);
    // Здесь будет вызван метод Worker::Dance, так он вызывается у переменной типа Worker
    worker.Dance();

    VisitNightClub(worker);
}

/*
Mario is dancing
Oppa!
Mario is dancing
*/

/*
Эту ошибку можно обнаружить во время компиляции, указав
спецификатор override у метода Worker::Dance. В этом случае
компилятор выдал бы ошибку при попытке переопределить
невиртуальный метод.
*/
