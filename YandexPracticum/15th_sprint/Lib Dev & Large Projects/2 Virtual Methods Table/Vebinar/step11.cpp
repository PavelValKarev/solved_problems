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

    //реализуем деструктор//
    ~MagicHat() {
        std::cout << "MagicHat::Dtor()"sv << std::endl;
    }

    MagicHat& operator = (const MagicHat&) = delete;
    
    static void SetVTable(MagicHat* obj) {        
        *(MagicHat::Vtable**)obj = &MagicHat::VTABLE;
    }
   
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
