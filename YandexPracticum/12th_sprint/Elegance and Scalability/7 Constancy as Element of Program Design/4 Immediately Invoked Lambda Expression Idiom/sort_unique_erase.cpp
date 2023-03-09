#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

vector<int> Sorted(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums;
}

vector<int> Unique(vector<int> nums) {
    auto it = unique(nums.begin(), nums.end());
    nums.erase(it, nums.end());
    return nums;
}

int main() {
    // Тогда инициализация вектора начнёт выглядеть немного странно:
    const vector<int> sorted_v = Unique(Sorted({ 1, 5, 9, 7, 15, 6, 1, 5, 9 }));
    //Иногда не хочется придумывать название для единожды используемой ф-ии
    //Тогда (в следующем примере) используется немедленно вызываемая лямбда ф-я
    //immediately invoked lambda expression

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
