#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Person {
    std::string name;
    int age;
};

bool comparePeople(const Person& p1, const Person& p2) {
    if (p1.name != p2.name) {
        return p1.name < p2.name;
    }
    return p1.age < p2.age;
}

int main() {
    std::vector<Person> people{
      {"Alice", 25},
      {"Bob", 30},
      {"Charlie", 20},
      {"David", 30},
      {"Eve", 25}
    };

    std::sort(people.begin(), people.end(), comparePeople);

    // Выводим отсортированный вектор:
    for (const auto& p : people) {
        std::cout << p.name << ", " << p.age << std::endl;
    }
}
