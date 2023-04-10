#include <iostream>

using namespace std;

struct Plate {
    char c1;
    int num;
    char c2;
    //поменяли местами два поля и размер структуры
    //стал 20 байт
    int region;
    char c3;
    
};
#include <iostream>

int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    cout << offsetof(Plate, c1) << endl;
    cout << offsetof(Plate, num) << endl;
    cout << offsetof(Plate, c2) << endl;
    cout << offsetof(Plate, region) << endl;
    cout << offsetof(Plate, c3) << endl;    
}
