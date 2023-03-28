//Рассмотрим другой пример — менеджер задач Практикума:

struct TaskPassResult {
    bool is_passed;
    // ...
};

class Task {
public:
    TaskPassResult RunCode(std::string_view code) const;
};

class TaskManager {
public:
    void RegisterTaskResult(int student_id, int task_id, TaskPassResult result);
    const Task& GetTask(int task_id) const;
};

//Метод для прохождения задания и получения оценки за него можно
//реализовать в классе когорты так:

class Cohort {
public:
    void PassTask(TaskManager& task_manager, int student_id, int task_id, std::string_view solution_code) {
        auto result = task_manager.GetTask(task_id).RunCode(solution_code);
        if (result.is_passed) {
            SetTaskPassed(student_id, task_id);
        }
        task_manager.RegisterTaskPass(student_id, task_id, std::move(result));
    }

    void SetTaskPassed(int student_id, int task_id);
};

//При вызове такого метода неясно, что он собирается изменять объект TaskManager:

cohort100.PassTask(task_manager, stident_id, task_id, code);

//Чтобы сделать побочный эффект более явным, применим декомпозицию — 
//разбиение задачи на подзадачи:

class Cohort {
public:
    // теперь TaskManager передаётся по константной ссылке
    [[nodiscard]] TaskPassResult PassTask(const TaskManager& task_manager, int student_id, int task_id, std::string_view solution_code) {
        auto result = task_manager.GetTask(task_id).RunCode(solution_code);
        if (result.is_passed) {
            SetTaskPassed(student_id, task_id);
        }
        return result;
    }

    void SetTaskPassed(int student_id, int task_id);
};

// ...
// метод не меняет task_manager, неявного побочного эффекта больше нет
auto result = cohort100.PassTask(task_manager, stident_it, task_id, code);
task_manager.RegisterTaskPass(student_id, task_id, std::move(result));
