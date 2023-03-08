#include <iostream>
#include <memory>
#include <string>
#include <cassert>

using namespace std;

struct Cat {
    Cat(const string& name, int age)
        : name_(name)
        , age_(age)  //
    {
        cout << name_ << " cat was created"s << endl;
    }
    const string& GetName() const noexcept {
        return name_;
    }
    int GetAge() const noexcept {
        return age_;
    }
    ~Cat() {
        cout << name_ << " cat was destroyed"s << endl;
    }
    void Speak() const {
        cout << "Meow!"s << endl;
    }

private:
    string name_;
    int age_;
};

int main() {
    // Создаёт экземпляр Cat в куче и возвращает unique_ptr
    auto cat1 = make_unique<Cat>("Tom"s, 2);
    // Следующая строчка не скомпилируется - экземпляры unique_ptr копировать нельзя
    //unique_ptr<Cat> cat2 = cat1;

    // Зато можно перемещать.
    //auto cat2 = std::move(cat1);
    unique_ptr<Cat> cat2 = std::move(cat1);

    assert(!cat1);
}
