#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

/*
Компаратор для std::sort должен возвращать true, если первый аргумент
меньше второго. Для сортировки в порядке возрастания, компаратор должен
вернуть true, если первый аргумент меньше второго. Для сортировки в
порядке убывания, компаратор должен вернуть true, если первый
аргумент больше второго.
*/

bool compareByName(const Person& a, const Person& b) {
    return a.name < b.name;
}

bool compareByAge(const Person& a, const Person& b) {
    return a.age < b.age;
}

int main() {
    std::vector<Person> people{ {"John", 25}, {"Alice", 35}, {"Bob", 20} };

    // Sort by name
    std::sort(people.begin(), people.end(), compareByName);

    for (const auto& person : people) {
        std::cout << person.name << " " << person.age << std::endl;
    }

    // Sort by age
    std::sort(people.begin(), people.end(), compareByAge);

    for (const auto& person : people) {
        std::cout << person.name << " " << person.age << std::endl;
    }

    return 0;
}
