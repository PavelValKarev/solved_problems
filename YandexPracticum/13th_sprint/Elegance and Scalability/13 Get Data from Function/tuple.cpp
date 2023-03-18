class Cohort {
public:
    using Raiting = int;
    using Clock = std::chrono::system_clock;
    std::tuple<const Student&, Raiting, Clock::time_point> FindBestStudent() const;
};
