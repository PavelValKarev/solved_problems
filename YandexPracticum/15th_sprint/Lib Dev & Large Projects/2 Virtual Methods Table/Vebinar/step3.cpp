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
    
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }    
};
