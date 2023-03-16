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

    // как раньше
    sort(lectures.begin(), lectures.end(), [](const Lecture& lhs, const Lecture& rhs) {
        return lhs.complexity < rhs.complexity;
        });

    // как теперь
    rng::sort(lectures, less<>{}, [](const Lecture& x) {
        return x.complexity;
        });

    return 0;
}
