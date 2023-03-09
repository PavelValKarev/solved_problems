#include<vector>
#include<algorithm>
#include<iostream>
#include "log_duration.h"

using namespace std;

vector<int> Sorted(vector<int> nums) {
    sort(nums.begin(), nums.end());
    return nums;
}

int main() {

    //Другие примеры использования идиомы IILE — вычисление
    //времени конструирования объекта 
    const vector<int> sorted_v = [] {
        LOG_DURATION("Sorted vector initialization"s);
        return Sorted({ 1, 5, 9, 7, 15, 6, 1, 5, 9 });        
    }();   
}
