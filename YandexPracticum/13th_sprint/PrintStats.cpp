#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

struct Stats {
    int total;
    int females;
    int males;
    int employed_females;
    int unemployed_females;
    int employed_males;
    int unemployed_males;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename iterator_traits<InputIt>::value_type> range_copy(
        range_begin,
        range_end
    );
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

Stats ComputeStats(vector<Person> persons) {
    //                 persons
    //                |       |
    //          females        males
    //         |       |      |     |
    //      empl.  unempl. empl.   unempl.

    // пропускаем женщин вперед
    auto females_end = partition(
        begin(persons), end(persons),
        [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    
    //до конца женщин - вперед работающих
    auto employed_females_end = partition(
        begin(persons), females_end,
        [](const Person& p) {
            return p.is_employed;
        }
    );

    //затем от конца женщин начались мужчины
    //пропускаем вперед работающих мужчин
    auto employed_males_end = partition(
        females_end, end(persons),
        [](const Person& p) {
            return p.is_employed;
        }
    );

    return {
         ComputeMedianAge(begin(persons), end(persons)),
         ComputeMedianAge(begin(persons), females_end),
         ComputeMedianAge(females_end, end(persons)),
         ComputeMedianAge(begin(persons),  employed_females_end),
         ComputeMedianAge(employed_females_end, females_end),
         ComputeMedianAge(females_end, employed_males_end),
         ComputeMedianAge(employed_males_end, end(persons))
    };
}

void PrintStats(vector<Person> persons) {

    Stats stats = ComputeStats(persons);

    cout << "Median age = "
        << stats.total << endl
        << "Median age for females = "
        << stats.females << endl
        << "Median age for males = "
        << stats.males << endl
        << "Median age for employed females = "
        << stats.employed_females << endl
        << "Median age for unemployed females = "
        << stats.unemployed_females << endl
        << "Median age for employed males = "
        << stats.employed_males << endl
        << "Median age for unemployed males = "
        << stats.unemployed_males << endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
