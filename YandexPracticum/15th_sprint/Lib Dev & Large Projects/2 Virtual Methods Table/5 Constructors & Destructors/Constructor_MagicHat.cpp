#include <iostream>
#include <vector>

using namespace std;

//функция для печати адреса виртуальной таблицы
void PrintVptr(void* obj) {
    auto ptr = reinterpret_cast<size_t*>(obj);
    cout << "Vptr : "s << *ptr << endl;
}

class MagicHat {
public:
    MagicHat() {
        cout << "MagicHat::Ctor : "s;
        PrintVptr(this);
    }
    ~MagicHat() {
        cout << "MagicHat::Dtor : "s;
        PrintVptr(this);
    }
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }
};

class HatWithApples : public MagicHat {
public:
    HatWithApples() {
        cout << "HatWithApples::Ctor : "s;
        PrintVptr(this);
    }
    ~HatWithApples() {
        cout << "HatWithApples::Dtor : "s;
        PrintVptr(this);
    }
    void WhatInside() const {
        cout << "Apple"s << endl;
    }
    bool HasComethingInside() const {
        cout << "Yes. Something red and tasty"s << endl;
        return true;
    }
private:
    /* 10 яблок лежало в шляпе */
    int apples_count = 10;
};

class HatWithRabbits : public MagicHat {
public:
    HatWithRabbits() {
        cout << "HatWithRabbits::Ctor : "s;
        PrintVptr(this);
    }
    ~HatWithRabbits() {
        cout << "HatWithRabbits::Dtor : "s;
        PrintVptr(this);
    }
    void WhatInside() const {
        cout << "Rabbit"s << endl;
    }
    bool HasComethingInside() const {
        cout << "Yes. Several furry carrot lovers"s << endl;
        return true;
    }

private:
    /* 3 кролика сидело в шляпе */
    int rabbits_count = 3;
    /* каждому кролику полагается две морковки, чтобы пережить фокус без стресса */
    int carrot_count = 6;
};

class HatWithDoves : public MagicHat {
public:
    HatWithDoves() {
        cout << "HatWithDoves::Ctor : "s;
        PrintVptr(this);
    }
    ~HatWithDoves() {
        cout << "HatWithDoves::Dtor : "s;
        PrintVptr(this);
    }
    void WhatInside() const {
        cout << "Dove"s << endl;
    }
    bool HasSomethingInside() const {
        cout << "Yes. Flying simbol of peace"s << endl;
        return true;
    }
};

int main() {
    HatWithApples hat1;
    HatWithRabbits hat2;
    HatWithDoves hat3;   

    return 0;
}

/*
Внутри каждого объекта прячется объект базового класса.
Поэтому каждому объекту вызывается два конструктора, а
потом два деструктора соответственно.
*/

/*
В конструкторе базового объекта MagicHat указатель vtpr
указывает на одну таблицу, а в конструкторе HatWithApples
— уже на другую. Иными словами, указатель vptr перед
вызовом конструктора устанавливается на таблицу
виртуальных функций того класса, конструктор которого
вызывается. Это нужно, чтобы внутри конструктора
гарантированно вызывать только методы именно данного класса.
Такой механизм гарантирует, что конструктор базового
объекта не попытается обратиться к методам класса-наследника,
который на данный момент ещё не сконструирован.
*/
