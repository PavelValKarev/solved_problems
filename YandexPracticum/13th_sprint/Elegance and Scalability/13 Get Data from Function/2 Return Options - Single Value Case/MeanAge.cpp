#include <optional>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Student {
public:
    Student(string name, int age)
        :name_(name)
        , age_(age) {
    }

    int GetAge() const {
        return age_;
    }
private:
    string name_;
    int age_;
};

class Cohort {
    // ...
public:

    Cohort(vector<Student> students) : students_(students) { }

    std::optional<double> ComputeMeanAge() const {
        int total_sum = 0;
        size_t total_count = students_.size();

        // обработаем случай отсутствия студентов
        if (total_count == 0) {
            return std::nullopt;
        }

        for (const Student& student : students_) {
            total_sum += student.GetAge();
        }

        return static_cast<double>(total_sum) / total_count;
    }

private:
    vector<Student> students_;
};

int main() {

    Student student1("Pavel"s, 43);
    Student student2("Stepan"s, 23);
    Student student3("Mr. Drakula"s, 333);

    vector<Student> students{ student1, student2, student3 };

    Cohort cohort(students);
       
    //проверка - есть ли реальное значение
    if (auto d = cohort.ComputeMeanAge(); d)
        std::cout << "MeanAge is " << *d << '\n';
    else
        std::cout << "MeanAge is null\n";

    return 0;
}
