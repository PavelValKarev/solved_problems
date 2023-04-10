#include <iostream>
#include <vector>

using namespace std;

template <typename ... Args>
auto Sum(const Args& ... args) {
	//этот бинарный оператор будет применен для всех args
	return (args + ...);
}

int main() {
	cout << Sum(1, 2, 3) << endl;
	cout << Sum(1.5, 2.7, 1.3, 10.0) << endl;
}
