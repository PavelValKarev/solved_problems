#include<vector>
#include<algorithm>
#include<iostream>
//-------------------------
#include "functional"

using namespace std;

vector<int> Sorted(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums;
}

int main() {

    /*
    Используя идиому IILE, нужно не забывать об удобстве для читателя кода.
    Ведь код пишется однажды, а читается много раз. Если заменить явное
    указание типа объекта на auto, код может быть понят неправильно:
    */

    /*
    Увидев первую строчку, читатель решит, что sorted_v — это объект
    лямбда-функции. И мало кто обратит внимание на круглые скобки в конце.
    Дальше читатель запутается, ему придётся возвращаться и разбираться,
    что скрыто за auto. Чтобы показать явно, что вам нужна
    не лямбда-функция, а результат её вызова, можно воспользоваться
    функцией std::invoke. Для этого не забудьте подключить
    файл <functional>:
    */

    const vector<int> sorted_v = invoke( [] {
        vector<int> nums = Sorted({ 1, 5, 9, 7, 15, 6, 1, 5, 9 });
        auto it = unique(nums.begin(), nums.end());
        nums.erase(it, nums.end());
        return nums;
    });

    int n;
    // прочитаем n чисел из потока ввода и найдём их в sorted_v
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cout << x << ' ';
        cout << std::binary_search(sorted_v.begin(), sorted_v.end(), x) << endl;
    }
}
