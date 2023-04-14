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
        cout << "MagicHat::Ctor"s;
        if (HasSomethingInside()) {
            WhatInside();
        }
    }
    ~MagicHat() {
        cout << "MagicHat::Dtor"s;
        PrintVptr(this);
    }
    virtual void IsMagicHat() const {
        cout << "MagicHat:: I'm a magic hat"s << endl;
    }

    /*
    Пусть теперь методы WhatInside и HaveSomethingInside
    станут абстрактными. Оставим их реализацию во всех
    классах-наследниках, но объявим их = 0 в классе MagicHat:
    */
    virtual void WhatInside() const = 0;    
    virtual bool HasSomethingInside() const = 0;
};

class HatWithApples : public MagicHat {
public:
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
    /* каждому кролику полагается две морковки, чтобы пережить
    фокус без стресса */
    int carrot_count = 6;
};

class HatWithDoves : public MagicHat {
public:
    void WhatInside() const {
        cout << "Dove"s << endl;
    }
    bool HasSomethingInside() const {
        cout << "Yes. Flying simbol of peace"s << endl;
        return true;
    }
};

/*
Теперь при всём желании пользователь не сможет создать объект
класса MagicHat в своей программе. Такой код не скомпилируется,
несмотря на то что пользователь вызывает метод, определённый
в MagicHat:
*/

int main() {
    MagicHat hat;
    hat.IsMagicHat();
}
