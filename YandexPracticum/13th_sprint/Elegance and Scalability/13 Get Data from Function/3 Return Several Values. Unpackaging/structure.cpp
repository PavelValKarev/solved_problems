//для устраненния неоднозначности удобно использовать структуру
class Cohort {
public:
    using StudentList = std::vector<Student>;
    struct PushResult {
        StudentList pushed_students;
        StudentList ready_students;
    };
    PushResult PushStudents();
};

//распаковка при этом продолжит работать
auto [pushed, ready] = cohort100.PushStudents();

//! во время распаковки как и во время конструирования
//! учитывается только порядок полей, а не их названия
