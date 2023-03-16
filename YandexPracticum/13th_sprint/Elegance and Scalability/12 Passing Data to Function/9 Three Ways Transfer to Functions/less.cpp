#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };

    std::sort(v.begin(), v.end(), std::less<>());

    for (const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
