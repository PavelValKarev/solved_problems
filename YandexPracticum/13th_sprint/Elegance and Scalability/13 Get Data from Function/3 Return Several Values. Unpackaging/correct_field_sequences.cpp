#include<string>

using namespace std;

struct NamedPoint {
    string name;
    int x;
    int y;
};

NamedPoint getLastPoint();

//допустим мы получаем результат из функции распаковкой
auto [name, x, y] = getLastPoint();
string full_text = name + " ("s + to_string(x) + ","s + to_string(y) + ")"s;

/*
Если поменять поля x и y местами, то конструкция 
auto [name, x, y] = getLastPoint(); 
приведёт к нежелательному результату: переменная x
программы получит координату y, а переменная y — координату x.
*/

/*
Если мы изменим структуру, поменяв порядок типов полей,
то компилятор сможет предупредить об ошибке
*/
