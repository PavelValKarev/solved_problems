#include <iostream>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, int age)
        : name_(name)
        , age_(age) {
    }

    int GetAge() const { return age_; }
    const string& GetName() const { return name_; }
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

/*
Публичное наследование позволяет приводить тип ссылок и указателей, ссылающихся
на экземпляры классов-наследников, вверх по иерархии классов и тем самым
одинаково работать с наследниками через указатели и ссылки на родительский класс.
Благодаря этому можно в одном контейнере хранить указатели типа Person*,
которые в действительности могут ссылаться на любой из его наследников:
*/

int main() {
    Person boy("Harry Potter"s, 11);
    Worker worker("Mario"s, 40, WorkerSpeciality::PLUMBER);
    vector<const Person*> people{ &boy, &worker };

    for (const Person* person : people) {
        VisitNightClub(*person);
    }
}
