#include <iostream>
#include <optional>

using namespace std;

// не самый эффективный тест на простоту числа
bool IsPrime(int n) {
    if (std::abs(n) < 2) {
        return false;
    }

    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

template <typename Callback>
void GetPrimeNumbers(int from, int to, Callback callback) {
    for (int i = from; i < to; ++i) {
        if (IsPrime(i)) {
            callback(i);
        }
    }
}

/*
Использовать callback вместо уже готового итератора немного
сложнее, потому что нужно написать лямбда-функцию, но зато этот
способ ещё более универсальный. Например, так можно вывести
только числа-близнецы:
*/

int main() {
    optional<int> prev;
    GetPrimeNumbers(0, 100, [&prev](int p) {
        if (prev && p - *prev == 2) {
            cout << *prev << "-"sv << p << " "sv;
        }
        prev = p;
        });
}
