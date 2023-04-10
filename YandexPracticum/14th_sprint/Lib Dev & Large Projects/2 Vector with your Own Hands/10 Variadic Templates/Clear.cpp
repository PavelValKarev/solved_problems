#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename ... Args>
void PrintSizes(const Args& ... args) {
	((cout << args.size() << endl), ... );
}

template <typename ... Args>
void Clear(Args& ... args) {
	//оператор "запятая"
	(args.clear(), ...);
}

int main() {
	vector v = { 1, 2, 3};
	string s = "Hello"s;
	PrintSizes(v, s);
	cout << endl;
	Clear(v, s);
	PrintSizes(v, s);
}
