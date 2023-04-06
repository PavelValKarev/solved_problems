/*
Неопределённое поведение может поджидать и когда пишете исключительно
идиоматичный код на C++. Рассмотрим программу, которая создаёт сетку
з точек. Она начнёт с одной точки, затем создаст её дубликат со
смещением по горизонтали. Продублирует эту пару точек, чтобы получить
четыре, а потом проделает то же самое с четырьмя.
*/

/*
Проблема вызвана модификацией вектора в цикле range-based for.
*/
/*
Проблема функций DuplicateAlongX и DuplicateAlongY в том, что они
изменяют вектор точек в процессе итерирования по нему.
*/

#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y)
        : x(x)
        , y(y) {
    }
};


/*
Возможно, вы захотите использовать метод reserve, чтобы избавиться от переаллокации
и зарезервировать в векторе место, вдвое превышающее его текущий размер:
- Можно ли считать, что проблема с кодом исправлена?
- Проблема осталась. Тысяча чертей!

Если новый размер вектора больше, чем вместимость, все итераторы и ссылки,
включая end-итератор, становятся недействительными. В противном случае
недействительным становится только end-итератор.
Из этого замечания следует, что итератор, который возвращается из метода
end, всегда инвалидируется при вызове emplace_back. А это именно тот
итератор, который получен при инициализации range-based цикла for. 
Сравнение с таким итератором — неопределённое поведение.

Здесь не получится написать реализацию функций DuplicateAlong с использованием
цикла range-based for. Следует выбрать обычный цикл, использующий индексы:
*/
void DuplicateAlongX(vector<Point>& v, int offset) {
    v.reserve(v.size() * 2);
    for (const auto& p : v) {
        v.emplace_back(p.x + offset, p.y);
    }
}

void DuplicateAlongY(vector<Point>& v, int offset) {
    v.reserve(v.size() * 2);
    for (const auto& p : v) {
        v.emplace_back(p.x, p.y + offset);
    }
}

int main() {
    vector points = { Point(0, 0) };

    DuplicateAlongX(points, 1);
    DuplicateAlongX(points, 2);
    DuplicateAlongX(points, 4);

    // Дублируем точки по оси Y
    DuplicateAlongY(points, 1);
    DuplicateAlongY(points, 2);
    DuplicateAlongY(points, 4);

    int n = 0;
    for (const auto& p : points) {
        cout << '{' << p.x << ", "sv << p.y << "} "sv;
        ++n;
        if (n == 8) {
            cout << endl;
            n = 0;
        }
    }
}
