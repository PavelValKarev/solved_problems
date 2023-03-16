#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main() {

    vector<int> numbers = { 1, 2, 5, 6, 0, 9 };

    /*
     можно использовать std::ranges::subrange для создания
     диапазона, который будет охватывать только первые 5
     элементов, и изменять элементы этого диапазона в цикле
     for. Также нужно использовать ссылки на элементы, чтобы
     изменения были отражены в векторе numbers.
    */

    auto subrange = numbers | std::views::take(5);
    for (int& x : subrange) {
        ++x;
    }

    // вывод элементов последовательности
    for (auto p : numbers) {
        std::cout << p << ' ' << endl;
    }

    return 0;
}
