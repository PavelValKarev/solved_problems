#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v = { 1, 10, 3, 6, 2, 9 };
    auto it = find(v.begin(), v.end(), 3);
    *it = 15;
}
