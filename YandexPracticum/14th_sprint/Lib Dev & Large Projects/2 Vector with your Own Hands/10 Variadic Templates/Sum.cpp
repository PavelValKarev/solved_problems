#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T Sum(const T& x) {
	return x;
}

//я-я принимающая переменное кол-во аргументов
template<typename T, typename ... Args>
//ф-я суммы первый аргумент принимает явно
//другие аргументы передаются по константной ссылке
T Sum(const T& x, const Args& ... args) {
//компилятор рекурсивно разворачивает ее вызов
	return x + Sum(args...);
}

int main() {
	cout << Sum(1, 2, 3) << endl;
	cout << Sum(1.5, 2.7, 1.3, 10.0) << endl;
}
