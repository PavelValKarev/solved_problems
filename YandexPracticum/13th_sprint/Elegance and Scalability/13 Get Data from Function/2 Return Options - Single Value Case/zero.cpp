class Cohort {
    // ...
public:
    double ComputeMeanAge() const {
        int total_sum = 0;
        size_t total_count = students.size();
        for (const auto& student : students) {
            total_sum += student.GetAge();
        }
        
        return static_cast<double>(total_sum) / total_count;
    }
};
