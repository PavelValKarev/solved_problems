enum class GraduateFailReason {
    NOT_ALL_SPRINTS_PASSED = 0, // не все спринты пройдены
    FINAL_TASK_NOT_APPROVED = 1, // финальное задание не прошло ревью
    INCOMPLETE_FUNDING = 2, // неполная оплата
    DIPLOMA_ALREADY_RECEIVED = 3  // диплом уже получен
};

struct Diploma {
    int x;
};

/*
Но сравним эти функции по производительности, ведь невнятность сигнатуры
может в какой-то мере компенсироваться скоростью исполнения. 
Для простоты Diploma будет состоять из одного поля типа int:
*/

//variant
std::variant<Diploma, GraduateFailReason> GraduateReturn(int student_id) {
    if (student_id % 10 == 0) {
        return Diploma{ student_id * 100 };
    }

    // возьмём номер ошибки от 0 до 3
    int fail_reason_id = (student_id / 10) % 4;
    return static_cast<GraduateFailReason>(fail_reason_id);
}

//throw
Diploma GraduateExcept(int student_id) {
    if (student_id % 10 == 0) {
        return { student_id * 100 };
    }

    // возьмём номер ошибки от 0 до 3
    int fail_reason_id = (student_id / 10) % 4;
    throw static_cast<GraduateFailReason>(fail_reason_id);
}
