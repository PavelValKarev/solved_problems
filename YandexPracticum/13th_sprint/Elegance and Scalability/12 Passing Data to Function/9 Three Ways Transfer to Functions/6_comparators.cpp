#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <string_view>

using namespace std;

template <typename T>
void TestComparator(T comp, std::string_view name) {
    vector v1{ 3, 1, 4, 555, 3, 4, 6, 3, 345, 53, 5, 345, 3 };
    vector v2 = v1;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end(), comp);

    cout << "Компаратор "sv << name << ": "sv << (v1 == v2 ? "OK"sv : "Fail"sv) << endl;
}

bool CmpFunction(int x, int y) {
    return x < y;
}

struct CmpObject {
    bool operator()(int x, int y) const {
        return x < y;
    }
};

int main() {

    setlocale(LC_ALL, "Ru");

    auto cmp_lambda = [](int x, int y) {
        return x < y;
    };

    TestComparator(CmpFunction, "функция"sv);
    TestComparator(CmpObject(), "объект"sv);
    TestComparator(std::less<>(), "std::less"sv);
    TestComparator(cmp_lambda, "лямбда-функция"sv);
    TestComparator(std::ref(cmp_lambda), "лямбда-функция по ссылке"sv);
    TestComparator(std::function(CmpFunction), "std::function"sv);
}
