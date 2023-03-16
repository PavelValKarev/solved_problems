#include <iostream>
#include <algorithm>
#include <vector>

/*
template< class InputIt1, class InputIt2 >
std::pair<InputIt1,InputIt2> mismatch( InputIt1 first1, InputIt1 last1, InputIt2 first2 );
template< class InputIt1, class InputIt2, class BinaryPredicate >
std::pair<InputIt1,InputIt2> mismatch( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );
*/

int main() {
    std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<int> v2{ 1, 2, 3, 4, 0, 6, 7, 8 };

    auto result = std::mismatch(v1.begin(), v1.end(), v2.begin());

    if (result.first == v1.end()) {
        std::cout << "The vectors are equal" << std::endl;
    }
    else {
        std::cout << "The first non-matching element is " << *result.first << " in the first vector, and "
            << *result.second << " in the second vector." << std::endl;
    }

    return 0;
}
