#include <iostream>
#include <vector>

using namespace std;

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
    virtual ~MagicHat() {
        cout << "MagicHat::Dtor : "s;
        PrintVptr(this);
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
};

int main() {   
    HatWithApples hat_with_rabbits;    
}
