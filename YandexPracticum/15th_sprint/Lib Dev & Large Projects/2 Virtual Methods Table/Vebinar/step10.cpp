class MagicHat {
public:
    //реализуем конструкторы////
    MagicHat() {
        MagicHat::SetVTable(this);
        std::cout << "MagicHat::Ctor()"sv << std::endl;
    }

    MagicHat(const MagicHat&) {
        MagicHat::SetVTable(this);
        std::cout << "MagicHat::Ctor()"sv << std::endl;
    }

    MagicHat& operator = (const MagicHat&) = delete;

    //метод установки указателя на таблицу виртуальных ф-ий
    static void SetVTable(MagicHat* obj) {
        //(new-type) expression
        /*
        C-style cast - это способ явного преобразования типа
        в языке C++. Синтаксис C-style cast выглядит как пара
        скобок с типом, которым нужно выполнить преобразование,
        перед выражением, которое нужно преобразовать. 
        Например, (int)3.14 - это C-style cast выражения с
        плавающей точкой в целое число.

        В данном случае, (MagicHat::Vtable*)obj = &MagicHat::VTABLE;
        - это явное преобразование типа указателя на объект класса
        MagicHat к указателю на таблицу виртуальных функций 
        MagicHat::Vtable*, которое выполняется с помощью C-style cast.
        Обычно такое преобразование выполняется для доступа к таблице
        виртуальных функций объекта, например, для вызова определенной
        виртуальной функции через указатель на базовый класс.
        - это считается грязным приемом. reiterpret_cast, const_cast 
        более подконтрольные компилятору приемы
        */
        /*
        - интересная особенность - используется указатель на указатель
        - т.к. на первом месте объекта хранится указаетль на 
        виртуальную таблицу
        - obj который мы принимаем является указателем на объект
        - поэтому мы можем привести к указателю на указаетель
        - т.е. изначально у нас есть указатель на объект, в нем
        мы добираемся на указаетль на таблицу и в нем мы ставим
        еще один указаетель
        - и когда мы разименовываем это дело, то добираемся до 
        адреса таблицы виртуальных ф-ий, которая хранится на 
        первом месте
        */
        /*
        И этой переменной мы присваиваем адрес таблицы виртуальных 
        ф-ий, которая есть в классе = &MagicHat::VTABLE
        */
        *(MagicHat::Vtable**)obj = &MagicHat::VTABLE;
    }
    //////////////////////////
    void WhatInside() const {        
        GetVtable()->inside_this(this);
    }

    void Delete() {
        GetVtable()->delete_this(this);
    }
   
    using InsideFunction = void(*)(const MagicHat*);
    using DeleteFunction = void(*)(MagicHat*);

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };
    
    const Vtable* GetVtable() const {
        return vptr_;
    }

    Vtable* GetVtable() {
        return vptr_;
    }    

private:
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
