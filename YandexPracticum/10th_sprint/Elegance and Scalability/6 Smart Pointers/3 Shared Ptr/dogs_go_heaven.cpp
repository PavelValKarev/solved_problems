// Example1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Dog {
public:
    explicit Dog(string name)
        : name_(move(name))  //
    {
        cout << name_ << " dog has been created"sv << endl;
    }

    ~Dog() {
        // Все псы попадают в рай
        cout << name_ << " dog has gone to heaven"sv << endl;
    }

private:
    string name_;
};

class Person {
public:
    explicit Person(string name)
        : name_(move(name)) {
    }

    ~Person() {
        cout << name_ << " has died"sv << endl;
    }

    // Стать владельцем собаки
    void OwnDog(shared_ptr<Dog> dog) {
        dog_ = move(dog);
    }

    const shared_ptr<Dog>& GetDog() const {
        return dog_;
    }

    // Перестаём владеть собакой
    void ReleaseDog() {
        dog_.reset();
        assert(!dog_);  // Указатель обнуляется после вызова reset
    }

private:
    string name_;
    shared_ptr<Dog> dog_;
};


int main() {
    // Жили-были Иван да Марья
    Person maria("Maria"s);
    Person ivan("Ivan"s);

    {
        // У Ивана была собака Белка
        shared_ptr<Dog> dog1(new Dog("Belka"s));
        ivan.OwnDog(dog1);

        // А у Марьи - Стрелка
        auto dog2 = make_shared<Dog>("Strelka"s);
        maria.OwnDog(dog2);

        // А вот у Хатико не было хозяина
        auto dog3 = make_shared<Dog>("Hatiko"s);

        // Прошли годы
        cout << "-----"sv << endl;
        cout << "Several years have passed"sv << endl;

        cout << "-----"sv << endl;

        // Стал Иван вместе с Марьей владеть её собакой
        cout << "Ivan owns Maria's dog"sv << endl;
        ivan.OwnDog(maria.GetDog());
        cout << "-----"sv << endl;

        // Ушла Марья от Ивана, оставив ему собаку
        cout << "Maria leaves her dog"sv << endl;
        maria.ReleaseDog();
        cout << "-----"sv << endl;

    }
}
