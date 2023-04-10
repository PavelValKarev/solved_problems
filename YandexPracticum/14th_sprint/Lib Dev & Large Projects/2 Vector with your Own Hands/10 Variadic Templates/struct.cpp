#include <iostream>
#include <vector>

using namespace std;

struct Point {
	int x, y, z;

	Point(int a, int b, int c)
		: x(a), y(b), z(c) {
	}
};

int main() {
	vector<Point> v;
	v.emplace_back(1, 2, 3);
	cout << v.size() << endl;
}
