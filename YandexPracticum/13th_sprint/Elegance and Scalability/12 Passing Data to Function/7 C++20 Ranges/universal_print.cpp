#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string_view>

namespace rng = std::ranges;
using namespace std;

template <rng::input_range Range>
void Print(const Range& range) {
    for (const auto& x : range) {
        cout << x << " "sv;
    }
    cout << endl;
}

template <typename T>
void Print(const T& x) {
    cout << x << endl;
}

int main() {
    vector v = { 4, 1, 7, 2, 3, 8 };
    rng::sort(v);
    Print(v);
    Print(123);
    Print("abc"sv);

    return 0;
}
