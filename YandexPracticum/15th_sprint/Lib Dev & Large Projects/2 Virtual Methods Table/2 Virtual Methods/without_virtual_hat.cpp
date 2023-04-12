#include <iostream>
#include <vector>

using namespace std;

class MagicHat {
public:
    /*virtual*/ void WhatInside() const {
        cout << "Nothing"s << endl;
    }
};

class HatWithApples : public MagicHat {
public:
    void WhatInside() const {
        cout << "Apple"s << endl;
    }
};

class HatWithRabbits : public MagicHat {
public:
    void WhatInside() const {
        cout << "Rabbit"s << endl;
    }
};

class HatWithDoves : public MagicHat {
public:
    void WhatInside() const {
        cout << "Dove"s << endl;
    }
};

void FocusPocus(const vector<MagicHat*> hats) {
    cout << "Let the magic begin..."s << endl;
    for (auto hat : hats) {
        hat->WhatInside();
    }
    //измерим шляпу
    cout << "But the size of magic hat is "s << sizeof(MagicHat) << endl;
}

int main() {
    HatWithApples hat1;
    HatWithRabbits hat2;
    HatWithDoves hat3;
    vector<MagicHat*> hats = { &hat1, &hat2, &hat3 };
    FocusPocus(hats);
}
