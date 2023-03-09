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

// Функция создаёт двухлетних котов с заданным именем
unique_ptr<Cat> CreateCat(const string& name) {
    return make_unique<Cat>(name, 2);
}

class Witch {
public:
    explicit Witch(const string& name)
        : name_(name) {
    }

    void SetCat(unique_ptr<Cat>&& cat) noexcept {
        cat_ = std::move(cat);
    }
    unique_ptr<Cat> ReleaseCat() noexcept {
        return std::move(cat_);
    }

private:
    string name_;
    unique_ptr<Cat> cat_;
};

/*
Так, можно создать кота, передать его волшебнице, а потом забрать у неё
обратно. При этом перемещении участвует только указатель. Сам объект, 
сколь бы «тяжёлым» он ни был, никуда не перемещается и не копируется:
*/

int main() {
    Witch witch("Hermione"s);
    witch.SetCat(CreateCat("Crookshaks"s));
    auto cat = witch.ReleaseCat();
    cat->Speak();

    Witch witch2("Ginny Weasley"s);
    witch2.SetCat(std::move(cat));
    assert(!cat);
}
