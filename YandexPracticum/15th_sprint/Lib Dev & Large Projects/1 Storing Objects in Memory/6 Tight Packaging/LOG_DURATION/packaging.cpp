#include <iostream>
#include <array>
#include <vector>

#include "log_duration.h"

using namespace std;

template <typename Plate>
void Test() {
    const size_t N = 500000;
    vector<Plate> plates(N);
    for (auto& plate : plates) {
        plate.c1 = rand() % 10;
        plate.num = rand() % 1000;
        plate.c2 = rand() % 10;
        plate.c3 = rand() % 10;
        plate.region = rand() % 1000;
    }

    LOG_DURATION(typeid(Plate).name());

    for (volatile Plate& plate : plates) {
        plate.c1 = (plate.c1 * 2) % 10;
        plate.region /= 5;
        plate.num = (plate.num + plate.region) % 1000;
        plate.region = (plate.region * 3) % 1000;
        plate.c2 -= plate.c3;
        plate.region = plate.c2;
        plate.c3 = (plate.c3 + 42) % 10;
        plate.region -= plate.c1;
        plate.c1 = (plate.c1 * 2) % 10;
        plate.region /= 5;
        plate.num = (plate.num + plate.region) % 1000;
        plate.region = (plate.region * 3) % 1000;
        plate.c2 -= plate.c3;
        plate.region = plate.c2;
        plate.c3 = (plate.c3 + 42) % 10;
        plate.region -= plate.c1;
        plate.c1 = (plate.c1 * 2) % 10;
        plate.region /= 5;
        plate.num = (plate.num + plate.region) % 1000;
        plate.region = (plate.region * 3) % 1000;
        plate.c2 -= plate.c3;
        plate.region = plate.c2;
        plate.c3 = (plate.c3 + 42) % 10;
        plate.region -= plate.c1;
    }
}

const static int N = 12;
const std::array<char, N> Letters = { 'A', 'B', 'E', 'K', 'M', 'H', 'O', 'P', 'C', 'T', 'Y', 'X' };

#pragma pack(push, 1)
struct PackedPlate {
    uint32_t num : 10;
    uint32_t region : 10;
    uint32_t c1 : 4;
    uint32_t c2 : 4;
    uint32_t c3 : 4;
};
#pragma pack(pop)

struct Plate {
    char c1;
    int num;
    char c2;
    char c3;
    int region;
};

int main() {
    Test<Plate>();
    Test<PackedPlate>();
    return 0;
}

/*
Разница очевидна. Процессору неудобно работать
с плотно упакованными структурами, поэтому код
значительно замедляется.
*/
