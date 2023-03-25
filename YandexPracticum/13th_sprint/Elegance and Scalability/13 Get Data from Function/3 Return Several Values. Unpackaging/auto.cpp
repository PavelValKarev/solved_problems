//разработаем сигнатуру метода вычисления лучшего
//студента и его рейтинга
//так можно вернуть из функции два значения

class Cohort {
public:
    using Raiting = int;
    std::pair<const Student&, Raiting> FindBestStudent() const;
};

//Так можно вернуть из функции два значения.Принять их удобнее
//всего, воспользовавшись прекрасной возможностью C++17 — распаковкой.
Cohort cohort100;
// ...
auto [best_student, raiting] = cohort100.FindBestStudent();
