#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <iostream>


using namespace std;

template <typename T>
optional<T> SafeAdd(T a, T b) {
    // при переполнении возвращается nullopt, иначе - сумма
    int64_t max_value = std::numeric_limits<int64_t>::max();
    int64_t min_value = std::numeric_limits<int64_t>::min();

    if (((a > 0) && (b > 0)) && (a > max_value - b)) {

        return nullopt;
    }

    if (((a < 0) && (b < 0)) && (a < min_value - b)) {

        return nullopt;
    }

    else {
        int64_t c = a + b;
        return c;
    }

}

int main() {
    int64_t a;
    int64_t b;
    cin >> a >> b;

    auto c = SafeAdd(a, b);

    if (c) {
        cout << *c << endl;
    }

    else {
        cout << "Overflow!"s << endl;
    }

}
