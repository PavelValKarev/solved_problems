#include <iostream>
#include <array>

using namespace std;

/*
Максимальное число, представимое в виде n бит вычисляется как 2^n-1
То есть 2 бита могут максимум представить число 2^2-1=3 (в двоичном
формате 3 = 11), 4 бита - 2^4 -1 = 15. В нашем случае 8 бит
недостаточно — максимум составит 255. А 10 бит как раз хватит.
Определим поля num и region как битовые:
*/


/*
Пока мы ничего не выиграли. Но вспомните, что поля c1 , c2 и c3
— это не просто символы, а буквы на автомобильном номере. В
автомобильных номерах используются не все символы, а только
12 из них. Создадим массив таких символов, и вместо самих символов
в структуре будем хранить индексы в этом массиве. Для хранения
чисел от 0 до 12 будет достаточно 4 бит:
*/

const static int N = 12;
const std::array<char, N> Letters = {
    'A', 'B', 'E', 'K', 'M', 'H', 'O', 'P', 'C', 'T', 'Y', 'X' };

#pragma pack(push, 1)
struct Plate {
    uint16_t num : 10;
    uint16_t region : 10;
    uint8_t c1 : 4;
    uint8_t c2 : 4;
    uint8_t c3 : 4;
};
#pragma pack(pop)

//Макрос offsetof невозможно применить к полям базового класса. 
int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    
    /*cout << offsetof(Plate, num) << endl;
    cout << offsetof(Plate, region) << endl;
    cout << offsetof(Plate, c1) << endl;
    cout << offsetof(Plate, c2) << endl;
    cout << offsetof(Plate, c3) << endl;*/
    
}
