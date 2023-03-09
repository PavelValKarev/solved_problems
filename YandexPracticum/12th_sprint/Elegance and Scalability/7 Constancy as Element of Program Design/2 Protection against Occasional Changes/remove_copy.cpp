#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>

// Рассмотрим функцию, которая копирует из одного вектора в другой все
// элементы, кроме равных определённому значению.

using namespace std;

template <typename T>
void CopyIfNotEqual(const vector<T>& src, vector<T>& dest, T value) {
    remove_copy(src.begin(), src.end(), back_inserter(dest), value);
}

void TestCopyIfNotEqual() {
    vector<int> values = { 1, 9, 2, 3, 5, 8, 4, 3, 5 };
    vector<int> values_copy;
    CopyIfNotEqual(values, values_copy, 3);
    vector<int> expected = { 1, 9, 2, 5, 8, 4, 5 };
    assert(expected == values_copy);
}

int main() {
    TestCopyIfNotEqual();

    return 0;
}
