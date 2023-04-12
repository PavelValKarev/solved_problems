#include <iostream>
#include <vector>

using namespace std;

class MagicHat {
public:
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }
    virtual bool HasSomethingInside() const {
        cout << "Nope"s << endl;
        return false;
    }
};

class HatWithApples : public MagicHat {
public:
    void WhatInside() const {
        cout << "Apple"s << endl;
    }
    bool HasSomethingInside() const {
        cout << "Yes. Something red and tasty"s << endl;
        return true;
    }
};

class HatWithRabbits : public MagicHat {
public:
    void WhatInside() const {
        cout << "Rabbit"s << endl;
    }
    bool HasSomethingInside() const {
        cout << "Yes. Several furry carrot lovers"s << endl;
        return true;
    }
};

class HatWithDoves : public MagicHat {
public:
    void WhatInside() const {
        cout << "Dove"s << endl;
    }
    bool HasSomethingInside() const {
        cout << "Yes. Flying simbol of peace"s << endl;
        return true;
    }
};

void FocusPocus(const vector<MagicHat*> hats) {
    cout << "Let the magic begin..."s << endl;
    int hat_num = 1;
    for (auto hat : hats) {
        cout << "Hat humber "s << hat_num++ << " : " << endl;
        cout << "    Has something inside : "s;
        if (hat->HasSomethingInside()) {
            cout << "    And it is : "s;
            hat->WhatInside();
        }
    }
    cout << "But the size of magic hat is "s << sizeof(MagicHat) << endl;
}

int main() {
    HatWithApples hat1;
    HatWithRabbits hat2;
    HatWithDoves hat3;
    vector<MagicHat*> hats = { &hat1, &hat2, &hat3 };
    FocusPocus(hats);
}
