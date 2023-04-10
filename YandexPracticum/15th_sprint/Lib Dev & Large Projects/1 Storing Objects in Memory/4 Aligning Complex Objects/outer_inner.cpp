#include <iostream>
#include <array>

using namespace std;

struct Inner {
    int i;
    char c;
};

struct Outer {
    Inner in1;
    Inner in2;
    char c;
};

int main() {
    cout << "Sizeof = "s << sizeof(Inner) << endl;
    cout << offsetof(Inner, i) << endl;
    cout << offsetof(Inner, c) << endl;
    cout << endl;
    cout << "Sizeof = "s << sizeof(Outer) << endl;
    cout << offsetof(Outer, in1) << endl;
    cout << offsetof(Outer, in2) << endl;
    cout << offsetof(Outer, c) << endl;
}
