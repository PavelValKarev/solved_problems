Вспомните смысл поля region и num. Это код региона и номер.
То есть каждое из этих полей точно не будет превосходить 1000.
В таком случае 4 байта — это слишком много. Для представления
чисел от 0 до 1000 достаточно 2 байт. Используем тип uint16_t,
сэкономив при этом суммарно 4 байта:
*/

struct Plate {    
    uint16_t num;
    uint16_t region;
    char c1;
    char c2;
    char c3;    
};

//Макрос offsetof невозможно применить к полям базового класса. 
int main() {
    cout << "Sizeof = "s << sizeof(Plate) << endl;
    
    cout << offsetof(Plate, num) << endl;
    cout << offsetof(Plate, region) << endl;
    cout << offsetof(Plate, c1) << endl;
    cout << offsetof(Plate, c2) << endl;
    cout << offsetof(Plate, c3) << endl;
    
}
