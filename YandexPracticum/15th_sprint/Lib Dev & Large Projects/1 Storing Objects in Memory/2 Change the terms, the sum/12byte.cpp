#include <iostream>

using namespace std;

struct Plate {
    
    int num;
    //поменяли местами два поля и размер структуры
    //стал 12 байт
    int region;
    char c1;
    char c2;    
    char c3;
    
};
#include <iostream>

int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    
    cout << offsetof(Plate, num) << endl;
    cout << offsetof(Plate, region) << endl;
    cout << offsetof(Plate, c1) << endl;
    cout << offsetof(Plate, c2) << endl;   
    cout << offsetof(Plate, c3) << endl;
    
}
