#include <iostream>
#include <vector>

using namespace std;

class MagicHat {
public:
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }
};

class HatWithApples : public MagicHat {
public:
    void WhatInside() const {
        cout << "Apple"s << endl;
    }
    bool HasComethingInside() const {
        cout << "Yes. Something red and tasty"s << endl;
        return true;
    }

private:
    /* 10 яблок лежало в шляпе */
    int apples_count = 10;
};

class HatWithRabbits : public MagicHat {
public:
    void WhatInside() const {
        cout << "Rabbit"s << endl;
    }
    bool HasComethingInside() const {
        cout << "Yes. Several furry carrot lovers"s << endl;
        return true;
    }

private:
    /* 3 кролика сидело в шляпе */
    int rabbits_count = 3;
    /* каждому кролику полагается две морковки, чтобы пережить фокус без стресса */
    int carrot_count = 6;
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

//функция для печати адреса виртуальной таблицы
void PrintVptr(void* obj) {
    auto ptr = reinterpret_cast<size_t*>(obj);
    cout << "Vptr : "s << *ptr << endl;
}

int main() {
    HatWithApples apple_hat1;
    HatWithApples apple_hat2;
    HatWithRabbits rabbit_hat1;
    HatWithRabbits rabbit_hat2;
    HatWithDoves dove_hat1;
    HatWithDoves dove_hat2;

    vector<MagicHat*> hats = { &apple_hat1, &apple_hat2,
                              &rabbit_hat1, &rabbit_hat2,
                              &dove_hat1, &dove_hat2 };
    for (auto hat : hats) {
        PrintVptr(hat);
    }

    return 0;
}
