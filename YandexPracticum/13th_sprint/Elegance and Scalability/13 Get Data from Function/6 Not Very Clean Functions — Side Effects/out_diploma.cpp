/*
Возврат через параметр
Побочный эффект может касаться параметров, передаваемых по неконстантной
ссылке или указателю. 
Это ещё один способ возврата из функции.
Таким способом можно заставить функцию возвращать несколько значений, и
он действительно был популярным до появления распаковки, а в некоторых
случаях и после.
*/

enum class GraduateFailReason {
    ALL_SUCCESS,
    NOT_ALL_SPRINTS_PASSED,    // не все спринты пройдены
    FINAL_TASK_NOT_APPROVED,   // финальное задание не прошло ревью
    INCOMPLETE_FUNDING,        // неполная оплата
    DIPLOMA_ALREADY_RECEIVED   // диплом уже получен
};

class Cohort {
public:
    GraduateFailReason Graduate(int student_id, Diploma& out_diploma);
    // ...
};

/*
Недостатки такой реализации:
- Нет возможности NRVO для диплома. 
NRVO возможно только для значения, возвращаемого через return.
- Нужно иметь уже сконструированный диплом для вызова функции.
сылка, которую передали в функцию, требует, чтобы объект уже существовал.
- Из кода вызова метода не ясно, что возврат производится в параметр.
*/
