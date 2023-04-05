#include <climits>
#include <iomanip>
#include <iostream>

bool TestSigned(int n) {
    return n < n + 1;
}

bool TestUnsigned(unsigned int n) {
    return n < n + 1;
}

using namespace std;
int main() {
    cout << boolalpha;
    cout << TestSigned(INT_MAX) << endl;
    cout << TestUnsigned(UINT_MAX) << endl;
}

/*
При сложении целых чисел без знака, например, unsigned int или uint32_t,
переполнение строго определено.
Tсли прибавить к значению UINT_MAX единицу, гарантируется, что результат
будет равен нулю.
*/
