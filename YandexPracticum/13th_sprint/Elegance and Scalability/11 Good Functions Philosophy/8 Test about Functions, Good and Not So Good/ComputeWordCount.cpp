#include <iostream>
#include <array>
#include <unordered_map>
#include <fstream>

using namespace std;

constexpr int MAX_PAGES = 1000;

size_t ComputeWordCount(istream& stream) {
    size_t word_count = 0;
    string word;
    while (stream >> word) {
        ++word_count;
    }
    return word_count;
}

int main() {
    ifstream in_file("input.txt"s);
    cout << ComputeWordCount(in_file);
}
