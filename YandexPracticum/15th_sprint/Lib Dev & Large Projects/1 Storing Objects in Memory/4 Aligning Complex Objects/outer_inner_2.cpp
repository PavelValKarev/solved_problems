#include <iostream>
#include <array>

using namespace std;

struct Inner {
    int i;
    char c;
};

struct Outer {
    Inner in1;
    char c;
    Inner in2;
    
};

int main() {
    cout << "Sizeof = "s << sizeof(Inner) << endl;
    cout << offsetof(Inner, i) << endl;
    cout << offsetof(Inner, c) << endl;
    cout << endl;
    cout << "Sizeof = "s << sizeof(Outer) << endl;
    cout << offsetof(Outer, in1) << endl;
    cout << offsetof(Outer, c) << endl;
    cout << offsetof(Outer, in2) << endl;
    
}
