// NRVO - Named Optimization 
// NRVO производится только если происходит возврат
// непосредственно именнованного значения

class Cohort {
public:
    // ...
    PushResult PushStudents() {
        StudentList ready_students = GetReadyStudents();
        StudentList students_to_push = GetOtherStudents(ready_students);
        for (Student& student : students_to_push) {
            PushStudent(student);
        }

        //в таком случае может произойти копирование возможно
        //немаленьких списков
        return { ready_students, students_to_push };  // неэффективно
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
        //в подобных случаях используйте std::move
        return { std::move(ready_students), std::move(students_to_push) }; // правильно
    }
};
