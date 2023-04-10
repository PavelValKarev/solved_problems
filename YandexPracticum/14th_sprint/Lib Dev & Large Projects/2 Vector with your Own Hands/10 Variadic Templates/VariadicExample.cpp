#include <iostream>

using namespace std;

/*
вариативный шаблон
позволяет создать шаблон функции или класса, принимающий любое число
параметров произвольных типов
*/
template <typename... Types>
void PrintArgumentCount(const Types&... values) {
    cout << sizeof...(values) << endl;
}

int main() {
    PrintArgumentCount();                    // Выведет 0
    PrintArgumentCount(42);                  // Выведет 1
    PrintArgumentCount("hello"s, 42, 1.23);  // Выведет 3
}
