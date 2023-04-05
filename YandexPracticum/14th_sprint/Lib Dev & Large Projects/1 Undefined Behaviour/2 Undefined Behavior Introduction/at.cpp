#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

int main() {
    vector v{ 1, 2, 3, 4 };
    try {
        cout << v.at(10) << endl;
    }
    catch (const exception& e) {
        cout << "Exception: "sv << e.what() << endl;
    }
}
