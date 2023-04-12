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

/*
С деструкторами, казалось бы, всё так же. Но здесь кроется небольшой подвох.
При компиляции не всегда известно, какой динамический тип у удаляемого объекта.
*/
int main() {
    
    /*
    Комментарий: При вызове delete должно случится следующее:
    Вызов деструктора соответствующего класса;
    Освобождение динамически выделенной памяти.
    Но во время компиляции может быть неизвестен динамический тип
    бъекта, поэтому использовать раннее связывание в первом пункте
    будет невозможно.
    */
    MagicHat* hat;
    if (0) {
        hat = new HatWithApples();
    }
    else {
        hat = new HatWithRabbits();
    }
    delete hat;

    return 0;
}

/*
В примере выше компилятор не может определить тип удаляемого 
объекта. Если в этот момент использовать раннее связывание и
вызвать деструктор только для MagicHat, не все ресурсы могут
быть освобождены корректно. Ведь на самом деле объект имеет
другой тип. Более того, компилятор может сообщить вам об
опасности через предупреждение:
*/

/*
В предупреждении есть подсказка, как решить проблему: просто
деструктор класса, содержащего виртуальные методы, тоже должен
быть виртуальным. Тогда позднее связывание решит задачу, будет
вызван деструктор из виртуальной таблицы соответствующего 
класса. Все ресурсы освободятся.
*/
