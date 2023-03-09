#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
    return IteratorRange{ v.begin(), next(v.begin(), min(top, v.size())) };
}

struct Person {
    string name{};
    int age{}, income{};
    bool is_male;
    bool is_female;
};

vector<Person> ReadPeople(istream& input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person& p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';

        p.is_female = gender == 'W';
    }
    return result;
}

vector<Person> SortByAge(vector<Person> people) {
    sort(people.begin(), people.end(),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        });
    return people;
}

void GetAdult(const vector<Person>& people) {
    int adult_age;
    cin >> adult_age;

    vector<Person> sorted_v = SortByAge(people);

    auto adult_begin = lower_bound(sorted_v.begin(), sorted_v.end(), adult_age,
        [](const Person& lhs, int age) {
            return lhs.age < age;
        });

    std::cout << "There are "s << distance(adult_begin, sorted_v.end()) << " adult people for maturity age "s
        << adult_age << '\n';
}

void SortByWealthy(vector<Person> people) {
    int count;
    cin >> count;

    //дает итератор на первый и последний элемент
    auto head = Head(people, count);

    partial_sort(head.begin(), head.end(), people.end(),
        [](const Person& lhs, const Person& rhs) {
            return lhs.income > rhs.income;
        });

    int total_income = accumulate(head.begin(), head.end(), 0, [](int cur, Person& p) {
        return p.income = p.income + cur;
        });
    std::cout << "Top-"s << count << " people have total income "s << total_income << '\n';
}

void SortByName(vector<Person> people, char gender) {

    IteratorRange range{ people.begin(), partition(people.begin(), people.end(),
                        [gender](Person& p) {
                            return gender == 'M' ? p.is_male : p.is_female;
                        }) };
    if (range.begin() == range.end()) {
        std::cout << "No people of gender "s << gender << '\n';
    }
    else {
        sort(range.begin(), range.end(),
            [](const Person& lhs, const Person& rhs) {
                return lhs.name < rhs.name;
            });
        const string* most_popular_name = &range.begin()->name;
        int count = 1;
        for (auto i = range.begin(); i != range.end();) {
            auto same_name_end = find_if_not(i, range.end(),
                [i](const Person& p) {
                    return p.name == i->name;
                });
            auto cur_name_count = distance(i, same_name_end);
            if (cur_name_count > count) {
                count = cur_name_count;
                most_popular_name = &i->name;
            }
            i = same_name_end;
        }
        std::cout << "Most popular name among people of gender "s << gender << " is "s << *most_popular_name << '\n';
    }
}

void BuildStatsData(vector<Person> people) {

    for (string command; cin >> command;) {
        using namespace std::string_literals;
        if (command == "AGE"s) {
            GetAdult(people);
        }
        else if (command == "WEALTHY"s) {
            SortByWealthy(people);
        }
        else if (command == "POPULAR_NAME"s) {
            char gender;
            cin >> gender;
            SortByName(people, gender);
        }
    }
}

int main() {
    vector<Person> people = ReadPeople(cin);

    BuildStatsData(people);

    return 0;
}
