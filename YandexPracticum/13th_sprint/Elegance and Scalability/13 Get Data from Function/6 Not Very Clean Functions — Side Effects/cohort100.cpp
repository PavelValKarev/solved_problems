
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
Вызывать метод будут как-нибудь так:
*/

int main() {

    Diploma new_diploma;

    auto err = cohort100.Graduate(student_to_graduate, new_diploma);

    if (err == ALL_SUCCESS) {
        cout << "Поздравляем с успешным завершением курса! Ваш диплом:\n"sv << new_diploma << endl;
    }
    else {
        cout << "Ошибка, код "sv << static_cast<int>(err) << endl;
    }

    return 0;
}

/*
Из вызова метода совершенно не ясно, что параметр new_diploma выходной:
cohort100.graduate(student_to_graduate, new_diploma).
Чтобы сделать код более внятным, можно заменить ссылку на указатель. 
Тогда вызов как бы скажет, что функция собирается изменить параметр:
cohort100.graduate(student_to_graduate, &new_diploma). 
Но добавится другая проблема — указатель в сигнатуре намекает на 
возможность передачи nullptr, что в этом случае не подразумевается.
Распаковка, variant и optional позволяют избавиться от возвращения
через параметр. Это нужно делать, чтобы лучше соответствовать прямому
назначению синтаксических элементов: return — для возврата, 
параметры — для передачи данных в функцию.
*/
