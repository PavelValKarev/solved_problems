#include <string>
#include <iostream>

/*
Использование Forwarding reference в паре с forward — это стандартный паттерн
в случае, если функция должна передать свой аргумент дальше, не задумываясь
о его типе, либо сохранить его в классе. Так выглядит правильная реализация
функции, вызывающей конструктор произвольного типа:
*/

using namespace std;

template <typename T, typename S>
T Construct(S&& arg) {
    return T(std::forward<S>(arg));
}

int main() {
    string s = Construct<string>("abc");
    int i = Construct<int>(1);

    cout << s << endl;
    cout << i;
}
