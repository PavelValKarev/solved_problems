class MagicHat {
public:
    //используем using чтобы сделать код более читаемым
    using InsideFunction = void(*)(const MagicHat*);
    using DeleteFunction = void(*)(MagicHat*);
    struct Vtable {       
        InsideFunction inside_this;
        DeleteFunction delete_this;
    };
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }    
};
