#include <iostream>
#include <array>

using namespace std;

struct X {
    int i1;
    array<char, 6> c;
    int i2;
    double d;
};

int main() {
    cout << "Sizeof = "s << sizeof(X) << endl;
    cout << offsetof(X, i1) << endl;
    cout << offsetof(X, c) << endl;
    cout << offsetof(X, i2) << endl;
    cout << offsetof(X, d) << endl;
}
