/*
Во-вторых, для поиска планеты не важен индекс элемента в массиве, 
поэтому цикл получится упростить, используя range-based for:

*/

bool IsPlanet(string_view name) {
    for (auto planet_name : PLANETS) {
        if (planet_name == name) {
            return true;
        }
    }
    return false;
}
//////////////////////////////////////////////////

/*
В этом цикле шанс ошибиться с индексами уже исключён. Можно пойти
дальше и избавиться от написания цикла вручную, заменив его на
подходящий здесь алгоритм std::find:
*/

#include <algorithm>
...
bool IsPlanet(string_view name) {
    return find(begin(PLANETS), end(PLANETS), name) != end(PLANETS);
}
