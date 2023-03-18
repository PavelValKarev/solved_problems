class Cohort {
public:
    // ...
    PushResult PushStudents() {
        StudentList ready_students = GetReadyStudents();
        StudentList students_to_push = GetOtherStudents(ready_students);
        for (Student& student : students_to_push) {
            PushStudent(student);
        }

        return {ready_students, students_to_push};  // неэффективно
    }
};



class Cohort {
public:
    // ...
    PushResult PushStudents() {
        StudentList ready_students = GetReadyStudents();
        StudentList students_to_push = GetOtherStudents(ready_students);
        for (Student& student : students_to_push) {
            PushStudent(student);
        }

        return {std::move(ready_students), std::move(students_to_push)}; // правильно
    }
};
