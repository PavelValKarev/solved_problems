#include <iostream>

using namespace std;

struct Plate {
    char c1;
    int num;
    char c2;
    char c3;
    int region;
};
#include <iostream>

int main() {
    cout << sizeof(Plate) << endl;
}

/*
16 байт. Все поля в этой структуре должны лежать по «коробочкам»
из 4 байт. Таким образом, c1 займёт не 1 байт, а 4. c2 и c3
поместятся в одну «коробочку», но и там возникнут пустые 2 байта.
Итого 11 байт для данных + 5 байт пустых.
*/
