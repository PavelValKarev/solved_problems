#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

template <typename InputIt1, typename InputIt2>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, ostream& out) {
    while (first1 != last1 && first2 != last2) {
        if (std::less<>()(*first1, *first2)) {
            out << *first1 << std::endl;
            //перемещает итератор на указанное количество вперед или назад
            advance(first1, 1);
        }
        else {
            out << *first2 << std::endl;
            //тоже перемещение на 1
            ++first2;
        }
    }
    while (first1 != last1) {
        out << *first1 << std::endl;
        ++first1;
    }
    while (first2 != last2) {
        cout << *first2 << std::endl;
        ++first2;
    }
}

// Реализуйте эти функции. Они должны вызывать ваш вариант функции Merge.
// Чтобы сократить кличество работы, можете реализовать вместо них одну шаблонную.
template<typename T>
void MergeSomething(const vector<T>& src1, const vector<T>& src2, ostream& out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
}

template <typename T, typename S>
void MergeSomething(const vector<T>& src1, const list<S>& src2, ostream& out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
}

template <typename S>
void MergeSomething(const string_view& src1, const list<S>& src2, ostream& out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
}

template <typename T, typename S>
void MergeSomething(const set<T>& src1, const vector<S>& src2, ostream& out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
}

// Реализуйте эту функцию:
template <typename T>
void MergeHalves(const vector<T>& src, ostream& out) {
    size_t mid = (src.size() + 1) / 2;
    // Сделать Merge участка вектора от 0 до mid и от mid до конца.
    // Элемент с индексом mid включается во второй диапазон.
    Merge(src.begin(), src.begin()+mid, src.begin()+mid, src.end(), out);
}


template <typename T>
void MergeHalves(std::vector<T>& v) {
    auto middle = v.begin() + v.size() / 2;
    Merge(v.begin(), middle, middle, v.end());
}

int main() {
    vector<int> v1{ 60, 70, 80, 90 };
    vector<int> v2{ 65, 75, 85, 95 };
    vector<int> combined{ 60, 70, 80, 90, 65, 75, 85, 95 };
    list<double> my_list{ 0.1, 72.5, 82.11, 1e+30 };
    string_view my_string = "ACNZ"sv;
    set<unsigned> my_set{ 20u, 77u, 81u };

    // пока функция MergeSomething реализована пока только для векторов
    cout << "Merging vectors:"sv << endl;
    MergeSomething(v1, v2, cout);

    cout << "Merging vector and list:"sv << endl;
    MergeSomething(v1, my_list, cout);

    cout << "Merging string and list:"sv << endl;
    MergeSomething(my_string, my_list, cout);

    cout << "Merging set and vector:"sv << endl;
    MergeSomething(my_set, v2, cout);

    cout << "Merging vector halves:"sv << endl;
    MergeHalves(combined, cout);
}
