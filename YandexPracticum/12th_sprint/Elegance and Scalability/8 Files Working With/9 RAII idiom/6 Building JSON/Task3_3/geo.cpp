#define _USE_MATH_DEFINES
#include "geo.h"

#include <cmath>

namespace geo {

double ComputeDistance(Coordinates from, Coordinates to) {
    using namespace std;
    if (from == to) {
        return 0;
    }
    static const double dr = M_PI / 180.;
    return acos(sin(from.lat * dr) * sin(to.lat * dr)
        + cos(from.lat * dr) * cos(to.lat * dr) * cos(abs(from.lng - to.lng) * dr))
        * 6371000;
}

// [Нужно исправить] `Coordinates` – лёгкий, передача по ссылке только добавит косвенное обращение к объекту и лишит некоторых
// оптимизаций связанных с адресами.
// [Павел: Сделано]
bool Coordinates::operator==(const Coordinates other) const {
    return lat == other.lat && lng == other.lng;
}

bool Coordinates::operator!=(const Coordinates other) const {
    return !(*this == other);
}

}  // namespace geo
