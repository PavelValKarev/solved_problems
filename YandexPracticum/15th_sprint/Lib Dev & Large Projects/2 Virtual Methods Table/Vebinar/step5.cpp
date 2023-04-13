class MagicHat {
public:
    //используем using чтобы сделать код более читаемым
    //здесь уходим от названия указателей
    using InsideFunction = void(*)(const MagicHat*);
    using DeleteFunction = void(*)(MagicHat*);

    struct Vtable {
        //-используем классические названия типов
        //-в этой структуре delete правильнее хранить
        //на первом месте
        DeleteFunction delete_this;
        InsideFunction inside_this;
        
    };        
    
    MagicHat::Vtable* vptr_ = nullptr;    
    static MagicHat::Vtable VTABLE;
    
    //реализуем методы, которые будут использоваться
    //в этой структуре. Они тоже должны быть 
    //статическими, так как таблица статическая
    static void Delete(MagicHat* obj){
        delete obj;
    }

    //через указатель можно было бы обращаться к полям
    //если бы они были
    static void WhatInside(const MagicHat*) {
        cout << "Nothing"sv << endl;
    }    
};
