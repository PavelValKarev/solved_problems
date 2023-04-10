#include <iostream>
#include <array>

using namespace std;

struct Plate {
    array<char, 3> letters;
    int digits;
    int region;
};

int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    cout << offsetof(Plate, letters) << endl;
    cout << offsetof(Plate, digits) << endl;
    cout << offsetof(Plate, region) << endl;    
}
