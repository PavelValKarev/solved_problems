#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

vector<int> Sorted(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums;
}

int main() {
    // создадим отсортированный вектор
    const vector<int> sorted_v = Sorted({ 1, 5, 9, 7, 15, 6 });
    // допустим, тут очень много разного кода
    //DoSomethingWithVector1(sorted_v);
    //DoSomethingElseWithVector(sorted_v);
    //DoOneMoreActionWithVector(sorted_v);
    // и еще много подобного кода

    //чтобы сберечь вектор выше от непреднамеренных
    //изменений нужно объявить его константным

    int n;
    // прочитаем n чисел из потока ввода и найдём их в sorted_v
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cout << x << ' ';
        cout << std::binary_search(sorted_v.begin(), sorted_v.end(), x) << endl;
    }
}
