#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Gender { FEMALE, MALE };

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

struct AgeStats {
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
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = range_copy.begin() + range_copy.size() / 2;
    nth_element(range_copy.begin(), middle, range_copy.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
        });
    return middle->age;
}

namespace StatsManager {
    static vector<Person> ReadPersons(istream& in_stream = cin);
    static AgeStats ComputeStats(vector<Person> persons);
    static void PrintStats(const AgeStats& stats, ostream& out_stream = cout);
};

vector<Person> StatsManager::ReadPersons(istream& in_stream) {
    int person_count;
    in_stream >> person_count;
    vector<Person> persons;
    persons.reserve(person_count);
    for (int i = 0; i < person_count; ++i) {
        int age, gender, is_employed;
        in_stream >> age >> gender >> is_employed;
        Person person{ age, static_cast<Gender>(gender), is_employed == 1 };
        persons.push_back(person);
    }
    return persons;
}

AgeStats StatsManager::ComputeStats(vector<Person> persons) {
    auto females_end = partition(persons.begin(), persons.end(), [](const Person& p) {
        return p.gender == Gender::FEMALE;
        });
    auto employed_females_end = partition(persons.begin(), females_end, [](const Person& p) {
        return p.is_employed;
        });
    auto employed_males_end = partition(females_end, persons.end(), [](const Person& p) {
        return p.is_employed;
        });

    return { ComputeMedianAge(begin(persons), end(persons)), ComputeMedianAge(begin(persons), females_end),
            ComputeMedianAge(females_end, end(persons)), ComputeMedianAge(begin(persons), employed_females_end),
            ComputeMedianAge(employed_females_end, females_end), ComputeMedianAge(females_end, employed_males_end),
            ComputeMedianAge(employed_males_end, end(persons)) };
}

void StatsManager::PrintStats(const AgeStats& stats, ostream& out_stream) {
    out_stream << "Median age = " << stats.total << endl
        << "Median age for females = " << stats.females << endl
        << "Median age for males = " << stats.males << endl
        << "Median age for employed females = " << stats.employed_females << endl
        << "Median age for unemployed females = " << stats.unemployed_females << endl
        << "Median age for employed males = " << stats.employed_males << endl
        << "Median age for unemployed males = " << stats.unemployed_males << endl;
}

int main() {
    StatsManager::PrintStats(StatsManager::ComputeStats(StatsManager::ReadPersons()));
    return 0;
}
