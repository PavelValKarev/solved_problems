#include <iostream>
#include <vector>
#include <algorithm>

namespace rng = std::ranges;
using namespace std;

struct Lecture {
    int course;
    int local_idx;
    int complexity;
};

vector<Lecture> ReadLectures() {
    vector<Lecture> result;
    return result;
}

int main() {
    vector<Lecture> lectures = ReadLectures();

    rng::sort(lectures, less<>{},
        [](const Lecture& x) {
            //Можно сортировать сразу по двум полям, используя tuple:
            return std::tuple{ x.course, x.local_idx };
        });

    return 0;
}
