#include <string>
#include <iostream>

using namespace std;

template <typename... Types>
void PrintArgumentCount(const Types&... values) {
    cout << sizeof...(values) << endl;
}

/*
Пакет параметров можно распаковать, написав после его имени многоточие. 
Распакованный пакет превращается в список элементов пакета, разделённых запятыми.
*/

// Функция Fn иллюстрирует распаковку пакета параметров при вызове функции
template <typename T, typename... Types>
void Fn(int arg1, const T& arg2, const Types&... values) {
    // Чтобы вызвать PrintArgumentCount, нужно распаковать пакет values
    PrintArgumentCount(arg1, arg2, values...);
    /* ... */
}

int main() {
    Fn(42, "Hello"sv, 4);         // Выведет 3
    Fn(42, 10.5);                 // Выведет 2
    Fn(3, "Goodbye"s, 42, 1.23);  // Выведет 4
}
