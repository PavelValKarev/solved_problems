class MagicHat {
public:
    //используем using чтобы сделать код более читаемым
    //здесь уходим от названия указателей
    using InsideFunction = void(*)(const MagicHat*);
    using DeleteFunction = void(*)(MagicHat*);

    struct Vtable {
        //используем классические названия типов
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    //создаем указатель на таблицу и по умолчанию
    //приравниваем его к nullptr
    MagicHat::Vtable* vptr_ = nullptr;

    //размещаем саму таблицу и называем ее VTABLE
    // !!! эту структуру нужно объявить статической
    //тогда она будет создана только один раз при
    //инициализации класса
    static MagicHat::Vtable VTABLE;
    
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }    
};
