#include <optional>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class Student {
public:

    Student(){
        name_ = {};
        age_ = 0;
        rating_ = 0;
    }

    Student(string name, int age, int rating)
        :name_(name)
        , age_(age)
    , rating_(rating) {
    }

    int GetAge() const {
        return age_;
    }

    int GetRating() const {
        return rating_;
    }

    string GetName() const {
        return name_;
    }    

private:
    string name_;
    int age_;
    int rating_;
};

bool CompRating(Student const &lhs, Student const& rhs) {
    return lhs.GetRating() < rhs.GetRating();
}

class Cohort {
    
public:

    Cohort(std::vector<Student> students) : students_(students) { }

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

    using Raiting = int;
    
    //здесь мы возвращаем ссылку на временный объект
    //это была огромная проблема
    std::pair<const Student&, Raiting> FindBestStudent()  {
        
       auto maxIt = std::max_element(students_.begin(), students_.end(), CompRating);
       
        // Извлекаем студента и его рейтинг из итератора
        const Student& maxStudent = *maxIt;
       
        int maxRating = maxStudent.GetRating();  

       //ссылку на временный объект удалось вернуть с помощью
       //изменения типа возвращаемого значения на константную ссылку
       return std::make_pair(std::cref(maxStudent), maxRating);      
        
    }

private:
    vector<Student> students_;   
};

int main() {

    Student student1("Stepan"s, 23, 67);
    Student student2("Pavel"s, 43, 99);
    Student student3("Mr. Drakula"s, 333, 3);

    vector<Student> students{ student1, student2, student3 };

    Cohort cohort(students);
       
    //проверка - есть ли реальное значение
    if (auto d = cohort.ComputeMeanAge(); d)
        std::cout << "MeanAge is " << *d << '\n';
    else
        std::cout << "MeanAge is null\n";

    cout << endl;

    auto best = cohort.FindBestStudent();

    cout << best.first.GetName() << " is the best student with rating " << best.second << endl;

    return 0;
}
