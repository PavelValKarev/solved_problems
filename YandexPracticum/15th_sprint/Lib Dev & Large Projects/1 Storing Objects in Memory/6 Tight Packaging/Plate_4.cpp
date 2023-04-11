#include <iostream>
#include <array>

using namespace std;

/*
У программиста есть инструмент сэкономить биты выравнивания, усложнив
при этом жизнь процессору. Это специальная директива pragma pack.
Она сообщает процессору, что никакого выравнивания у структуры быть
не должно. Все поля будут расположены одно за другим без учёта каких
бы то ни было удобных коробочек.
*/

#pragma pack(push, 1)
struct Plate {    
    uint16_t num;
    uint16_t region;
    char c1;
    char c2;
    char c3;    
};
#pragma pack(pop) 

//Макрос offsetof невозможно применить к полям базового класса. 
int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    
    cout << offsetof(Plate, num) << endl;
    cout << offsetof(Plate, region) << endl;
    cout << offsetof(Plate, c1) << endl;
    cout << offsetof(Plate, c2) << endl;
    cout << offsetof(Plate, c3) << endl;
    
}
