#include <iostream>
#include <array>

using namespace std;

struct Base1 {
    int i;
    char c;
};

struct Base2: Base1 {
    bool b;
    float f;
};

struct Outer : Base2 {
    short sh;
};

//Макрос offsetof невозможно применить к полям базового класса. 
int main() {
    cout << sizeof(Outer) << " "s
        << sizeof(Base1) << " "s
        << sizeof(Base2) << endl;
}
