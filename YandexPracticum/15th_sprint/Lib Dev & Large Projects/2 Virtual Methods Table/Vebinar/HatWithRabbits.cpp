#include <iostream>
#include <vector>

using namespace std;

class MagicHat {
public:
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }    
};

class HatWithRabbits : public MagicHat {
public:
    void WhatInside() const {
        cout << "Rabbit"s << endl;
    }    
};

void WhatInsideHat(const MagicHat* hat) {
    hat->WhatInside();
}

int main() {   
    HatWithRabbits hat_with_rabbits;
    WhatInsideHat(&hat_with_rabbits);
}
