#include <iostream>
#include <memory>
#include <new>
#include <string>

using namespace std;

#include <iostream>
#include <string>

using namespace std;

class Cat {
public:
    Cat(string name, int age)
        : name_(move(name))
        , age_(age)  //
    {
        cout << "Hello from " << name_ << endl;
    }

    ~Cat() {
        cout << "Goodbye from "sv << name_ << endl;
    }

    void SayHello() const {
        cout << "Meow, my name is "sv << name_ << ". I'm "sv << age_ << " year old."sv << endl;
    }

private:
    string name_;
    int age_;
};

int main() {
    Cat cat("Tom"s, 2);
    cat.SayHello();

    cout << endl;

    Cat* cat2 = new Cat("Leo"s, 3);
    cat2->SayHello();
    delete cat2;

    //Чтобы не забыть вызвать delete
    //для удаления объекта, используйте умный указатель unique_ptr:

    cout << endl;

    auto cat3 = make_unique<Cat>("Felix"s, 4);
    cat3->SayHello();

    cout << endl;
}
