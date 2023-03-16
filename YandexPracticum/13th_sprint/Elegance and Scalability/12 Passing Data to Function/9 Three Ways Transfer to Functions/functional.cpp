#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <string_view>

using namespace std;

// value_type из iterator_traits позволяет получить
// тип элемента по итератору
template <typename Iterator>
using IterValType = typename iterator_traits<Iterator>::value_type;

template <typename T>
using ComparatorByType = bool(const T& x, const T& y);

template <typename Iterator>
using ComparatorByIterator = ComparatorByType<IterValType<Iterator>>;

/*
Третий способ — std::function
Выше разобраны два способа передачи функции в функцию:
через шаблонный параметр, обладающий поразительной универсальностью, но невнятной сигнатурой;
через указатель на функцию, обладающий хорошей выразительностью, но совершенно не универсальный.
Есть третий способ — такой же универсальный, как шаблонный параметр, и такой же выразительный,
как указатель на функцию. Может быть, даже более выразительный. Он заключается в использовании
шаблонного класса std::function из файла <functional>. Этот класс позволяет сделать указатель
на функцию универсальным, способным принять любые компараторы и функциональные объекты.
Единственный шаблонный параметр класса std::function — тип указателя на функцию.
С std::function сигнатура универсальной функции, сортирующей диапазон чисел, выглядит так:

template <typename RandomIt>
void SortInt(RandomIt begin, RandomIt end, const function<bool(int, int)>& comp);

Из неё сразу видно, что третий параметр должен быть функциональным объектом, принимающим два
значения int и возвращающим bool. Такая сигнатура очень выразительна.
Можно сделать определённую выше функцию SortFuncPtr универсальной, добавив в неё function:

Проверим, что ни один компаратор не пострадал:

*/
template <typename RandomIt>
void SortFunction(RandomIt first, RandomIt last, const function<ComparatorByIterator<RandomIt>>& comp) {
    sort(first, last, ref(comp));
}

template <typename T>
void TestComparatorFunction(T comp, std::string_view name) {
    vector v1{ 3, 1, 4, 555, 3, 4, 6, 3, 345, 53, 5, 345, 3 };
    vector v2 = v1;

    sort(v1.begin(), v1.end());
    SortFunction(v2.begin(), v2.end(), comp);

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

    TestComparatorFunction(CmpFunction, "функция"sv);
    TestComparatorFunction(CmpObject(), "объект"sv);
    TestComparatorFunction(std::less<>(), "std::less"sv);
    TestComparatorFunction(cmp_lambda, "лямбда-функция"sv);
    TestComparatorFunction(std::ref(cmp_lambda), "лямбда-функция по ссылке"sv);
    TestComparatorFunction(std::function(CmpFunction), "std::function"sv);
}

