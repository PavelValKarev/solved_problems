#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

int main() {
    vector v{1, 2, 3, 4};
    cout << v[0] << endl;
    cout << v[10] << endl;
    cout << v[100] << endl;
    cout << v[1000] << endl;
    cout << v[10000] << endl;
    cout << v[100000] << endl;
}
