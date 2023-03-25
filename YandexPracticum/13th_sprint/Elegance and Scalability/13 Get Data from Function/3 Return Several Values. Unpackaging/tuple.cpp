//если нужно вернуть болшее чем два количество значений
//то подойдет класс tuple

class Cohort {
public:
    using Raiting = int;
    using Clock = std::chrono::system_clock;
    std::tuple<const Student&, Raiting, Clock::time_point> FindBestStudent() const;
};
