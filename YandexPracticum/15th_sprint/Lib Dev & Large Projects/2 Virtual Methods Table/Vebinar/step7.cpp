class MagicHat {
public:
    //реализуем публичные методы////////
    void WhatInside() const {
        vptr_->inside_this(this);
    }

    void Delete() {
        vptr_->delete_this(this);
    }
    ///////////////////////////////////
    using InsideFunction = void(*)(const MagicHat*);
    using DeleteFunction = void(*)(MagicHat*);

    struct Vtable {
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };

    static MagicHat::Vtable VTABLE;

private:
    MagicHat::Vtable* vptr_ = nullptr;
    
    static void Delete(MagicHat* obj) {
        delete obj;
    }

    static void WhatInside(const MagicHat*) {
        cout << "Nothing"sv << endl;
    }
};
