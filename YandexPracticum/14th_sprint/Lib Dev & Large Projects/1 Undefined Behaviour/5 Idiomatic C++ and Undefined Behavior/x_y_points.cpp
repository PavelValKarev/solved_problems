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

void DuplicateAlongX(vector<Point>& v, int offset) {
    for (const auto& p : v) {
        v.emplace_back(p.x + offset, p.y);
    }
}

void DuplicateAlongY(vector<Point>& v, int offset) {
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
