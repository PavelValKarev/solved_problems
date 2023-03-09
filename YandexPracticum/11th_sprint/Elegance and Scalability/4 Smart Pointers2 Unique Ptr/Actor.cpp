#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Actor {
    Actor(string name) : name_(move(name)) {
        cout << name_ << " was born! :)" << endl;
    }
    ~Actor() {
        cout << name_ << " died! :(" << endl;
    }
    void DoWork() {
        cout << name_ << " did some job! " << endl;
    }
private:
    string name_;
};

void run(Actor* ptr) {
    if (ptr) {
        ptr->DoWork();
    }
    else {
        cout << "An actor was expected :-/ " << endl;
    }
}

int main()
{
    auto ptr1 = make_unique<Actor>("Alice");
    auto ptr2 = make_unique<Actor>("Boris");
    //здесь Алиса удаляется, т.к. на нее больше никто не указывает
    ptr1 = move(ptr2);
    //ptr1 теперь указывает туда куда указывал ptr2 т.е. на Бориса
    run(ptr1.get());
    //а из ptr2 у нас было выполнено перемещение
    run(ptr2.get());
    return 0;
}
