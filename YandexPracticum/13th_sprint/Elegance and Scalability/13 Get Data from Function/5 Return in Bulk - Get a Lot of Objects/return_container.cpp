/*
Возврат контейнера по ссылке
Класс может реализовывать геттер для получения контейнера
\без передачи владения. В этом случае удобно использовать
псевдоним, чтобы можно было поменять контейнер, ничего
не нарушив в месте его применения:
*/

class Cohort {
public:
    using StudentMap = std::unordered_map<int, Student>;

    const StudentMap& GetAllStudents() const {
        return all_students_;
    }

private:
    StudentMap all_students_;
};

/*
Возвращать неконстантную ссылку, чтобы произвести какие-либо
операции с контейнером, не нужно. Это может привести к
неконсистентности данных класса и отбирает у него возможность
контролировать своё содержимое, что часто приводит к ошибкам:
*/

class Cohort {
public:
    using StudentMap = std::unordered_map<int, Student>;

    // плохо:
    StudentMap& GetAllStudents() {
        return all_students_;
    }

private:
    StudentMap all_students_;
};

// ...

Cohort cohort100;

// ...

// не делайте так:
cohort100.GetAllStudents[new_id] = move(new_student);

//Для допустимых изменений контейнера класса используйте отдельные методы:

class Cohort {
public:
    using StudentMap = std::unordered_map<int, Student>;

    const StudentMap& GetAllStudents() const {
        return all_students_;
    }

    int RegisterStudent(Student new_student) {
        // тут можно выполнить дополнительную инициализацию,
        // например открыть студенту доступ к первому спринту
    }

private:
    StudentMap all_students_;
};

// ...

Cohort cohort100;

// ...

int new_id = cohort100.RegisterStudent(move(new_student));
