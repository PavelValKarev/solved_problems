#include <iostream>
#include <array>

using namespace std;

struct X {
    array<int, 3> i;
    double d;
    char c;
};

int main() {
    cout << "Sizeof = "s << sizeof(X) << endl;
    cout << offsetof(X, i) << endl;
    cout << offsetof(X, d) << endl;
    cout << offsetof(X, c) << endl;    
}
