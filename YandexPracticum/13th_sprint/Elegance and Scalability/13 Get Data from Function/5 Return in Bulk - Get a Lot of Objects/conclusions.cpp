/*
Подведём итоги

С возвратом набора однотипных объектов всё сложнее, чем с передачей
его в функцию. При передаче владение объектами и контейнером продолжает
находиться под контролем вызывающей функции. А при возврате функция,
создавшая набор объектов, завершается и прекращает владение чем-либо.
Подведём итог урока, выбрав наиболее приемлемый способ получения набора
объектов для разных случаев.
Возвращается уже готовый набор объектов, которыми владеет класс. В этом
случае возвращаем контейнер по константной ссылке:
*/

class Cohort {
public:
    const std::vector<int>& GetGradesByStudent(int student_id) const {
        return grades_by_student_.at(student_id);
    }

private:
    std::map<int, std::vector<int>> grades_by_student_;
};

/*
Мы точно знаем, в каком контексте будет использоваться возвращаемое
значение, либо производительность не важна. В этом случае возвращаем
контейнер:
*/

class Cohort {
public:
    std::vector<int> GetUngradedStudents() const {
        std::vector<int> result;
        for (const auto& [id, grades] : grades_by_student_) {
            if (!grades.empty()) {
                result.push_back(id);
            }
        }
        return result;
    }

private:
    std::map<int, std::vector<int>> grades_by_student_;
};

/*
Хранить элементы — это основное назначение класса, и мы хотим итерироваться
по объекту класса. Тогда нужен возврат итераторов методами begin и end.
*/

class JSONArray {
public:
    using Container = std::vector<JSONelement>;

    Container::iterator begin() {
        return elements_.begin();
    }

    Container::iterator end() {
        return elements_.end();
    }

    // константные итераторы и cbegin, cend

private:
    Container elements_;
};

/*
Хотим позволить вызывающей стороне складывать в любой контейнер по её
желанию или даже сразу выводить в поток. В этом случае принимаем выходной
итератор:
*/

class Cohort {
public:
    template <typename OutputIt>
    std::vector<int> GetUngradedStudents(OutputIt dst) const {
        std::vector<int> result;
        for (const auto& [id, grades] : grades_by_student_) {
            if (!grades.empty()) {
                *dst++ = id;
            }
        }
        return result;
    }

private:
    std::map<int, std::vector<int>> grades_by_student_;
};

/*
Предполагаем, что вызывающая сторона может не сохранять объекты, а сразу
обрабатывать, либо хотим дать ей возможность прервать вычисление. Тогда
нужен наиболее универсальный способ — возврат через callback:
*/

template<typename Callback>
void GetPrimeNumbers(int from, int to, Callback callback) {
    for (int i = from; i < to; ++i) {
        if (IsPrime(i)) {
            callback(i);
        }
    }
}
