//если нужно вернуть болшее чем два количество значений
//то подойдет класс tuple
//например, если нужно вернуть не только студента,
//его рейтинг но и время когда он стал лучшим

class Cohort {
public:
    using Raiting = int;
    using Clock = std::chrono::system_clock;
    std::tuple<const Student&, Raiting, Clock::time_point> FindBestStudent() const;
};
