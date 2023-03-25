//Ранее вы увидели, как variant помогает возвратить объект или ошибку:

enum class GraduateFailReason {
    NOT_ALL_SPRINTS_PASSED,    // не все спринты пройдены
    FINAL_TASK_NOT_APPROVED,   // финальное задание не прошло ревью
    INCOMPLETE_FUNDING,        // неполная оплата
    DIPLOMA_ALREADY_RECEIVED   // диплом уже получен
};

std::variant<Diploma, GraduateFailReason> Graduate(int student_id);
