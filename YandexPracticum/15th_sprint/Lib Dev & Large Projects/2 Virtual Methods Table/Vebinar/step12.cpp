#include <iostream>
#include <vector>

using namespace std;

class MagicHat {
public:    
    MagicHat() {
        MagicHat::SetVTable(this);
        std::cout << "MagicHat::Ctor()"sv << std::endl;
    }

    MagicHat(const MagicHat&) {
        MagicHat::SetVTable(this);
        std::cout << "MagicHat::Ctor()"sv << std::endl;
    }

    MagicHat& operator = (const MagicHat&) = delete;
    
    ~MagicHat() {
        std::cout << "MagicHat::Dtor()"sv << std::endl;
    }

    void WhatInside() const {
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }

    using InsideFunction = void(*)(const MagicHat*);
    using DeleteFunction = void(*)(MagicHat*);    

    static void SetVTable(MagicHat* obj) {        
        *(MagicHat::Vtable**)obj = &MagicHat::VTABLE;
    }     
    
    struct Vtable;

    const Vtable* GetVtable() const {
        return vptr_;
    }

    Vtable* GetVtable() {
        return vptr_;
    }    

private:
    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    MagicHat::Vtable* vptr_ = nullptr;
    static MagicHat::Vtable VTABLE;
    
    static void Delete(MagicHat* obj) {
        delete obj;
    }

    static void WhatInside(const MagicHat*) {
        cout << "Nothing"sv << endl;
    }
};

//определяем саму таблицу, записываем в нее методы
MagicHat::Vtable MagicHat::VTABLE = { MagicHat::WhatInside, MagicHat::Delete };

class HatWithRabbits {
public:
    HatWithRabbits()
        : magic_hat_() {
        HatWithRabbits::SetVtable(this);
        std::cout << "HatWithRabbits::Ctor()"sv << std::endl;
    }

    HatWithRabbits(const HatWithRabbits& other)
        : magic_hat_(other.magic_hat_) {
        HatWithRabbits::SetVtable(this);
        std::cout << "HatWithRabbits::Ctor()"sv << std::endl;
    }

    HatWithRabbits& operator = (const HatWithRabbits&) = delete;

    //оператор преобразования к базовому классу
    //он возвращает экземпляр базового класса
    //который хранится на первом месте
    operator MagicHat() {
        return { magic_hat_ };
    }

    ~HatWithRabbits() {
        std::cout << "HatWithRabbits::Dtor()"sv << std::endl;
        //в классах наследниках не забываем переставлять 
        //указатель на таблицу базового класса при разрушении
        MagicHat::SetVTable((MagicHat*)this);
    }

    using InsideFunction = void(*)(const HatWithRabbits*);
    using DeleteFunction = void(*)(HatWithRabbits*);

    void WhatInside() const {
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    static void SetVtable(HatWithRabbits* obj) {
        *(HatWithRabbits::Vtable**)obj = &HatWithRabbits::VTABLE;
    }
    
    const Vtable* GetVtable() const {
        return (const HatWithRabbits::Vtable*)magic_hat_.GetVtable();
    }

    Vtable* GetVtable() {
        return (HatWithRabbits::Vtable*)magic_hat_.GetVtable();
    }

    static HatWithRabbits::Vtable VTABLE;

private:
    //на первом месте храним экземпляр базового класса
    MagicHat magic_hat_;

    static void Delete(HatWithRabbits* obj) {
        delete obj;
    }

    static void WhatInside(const HatWithRabbits*) {
        std::cout << "Rabbit!"sv << std::endl;
    }
};

HatWithRabbits::Vtable HatWithRabbits::VTABLE = {
    HatWithRabbits::WhatInside, HatWithRabbits::Delete
};

void WhatInsideHat(MagicHat* hat) {
    hat->WhatInside();
}

int main() {
    /*
    - создаем указатель на базовый класс
    - в него подставляем экземпляр класса наследника,
    преобразованный к указателю на базовый класс
    */    
    MagicHat* hat = (MagicHat*)(new HatWithRabbits());
    /*
    - вызов ф-ии, принимающей указатель на экземпляр 
    базового класса, в которой происходит вызов
    метода WhatInside()
    */
    WhatInsideHat(hat);
    /*
    т.к. построение через new, то удалить объект 
    тоже нужно корректно
    */
    hat->Delete();    
}
