#include <iostream>

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

/*
В предыдущей теме вы подробно изучили вопрос передачи функционального
объекта в качестве параметра. Его же можно использовать и для возврата
из функции. Этот способ напоминает выходной итератор, вместо которого 
можно применить callback, вызываемый при поступлении нового объекта:
*/

template <typename Callback>
void GetPrimeNumbers(int from, int to, Callback callback) {
    for (int i = from; i < to; ++i) {
        if (IsPrime(i)) {
            callback(i);
        }
    }
}

int main() {
    GetPrimeNumbers(0, 100, [](int p) {
        cout << p << " "sv;
        });
}
