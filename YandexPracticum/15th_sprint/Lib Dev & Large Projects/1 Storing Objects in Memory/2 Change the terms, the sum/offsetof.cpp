#include <iostream>

using namespace std;

struct Plate {
    char c1;
    int num;
    char c2;
    char c3;
    int region;
};

int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    cout << offsetof(Plate, c1) << endl;
    cout << offsetof(Plate, num) << endl;
    cout << offsetof(Plate, c2) << endl;
    cout << offsetof(Plate, c3) << endl;
    cout << offsetof(Plate, region) << endl;
}
/*
Используем макрос offsetof. Он позволяет узнать, какое 
смещение в байтах имеет поле относительно начала объекта:
*/
