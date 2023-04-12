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
    
    MagicHat::Vtable* vptr_ = nullptr;    
    static MagicHat::Vtable VTABLE;
    
    //реализуем методы, которые будут использоваться
    //в этой структуре. Они тоже должны быть 
    //статическими, так как таблица статическая
    static void Delete(MagicHat* obj){
        delete obj;
    }

    static void WhatInside(const MagicHat*) {
        cout << "Nothing"sv << endl;
    }    
};
