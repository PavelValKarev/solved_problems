#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

vector<int> Sorted(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums;
}

int main() {
    
    //Применение немедленно вызываемой лямбды
    //immediately invoked lambda expression
    const vector<int> sorted_v = [] {
        vector<int> nums = Sorted({ 1, 5, 9, 7, 15, 6, 1, 5, 9 });
        auto it = unique(nums.begin(), nums.end());
        nums.erase(it, nums.end());
        return nums;
    }() ;

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
