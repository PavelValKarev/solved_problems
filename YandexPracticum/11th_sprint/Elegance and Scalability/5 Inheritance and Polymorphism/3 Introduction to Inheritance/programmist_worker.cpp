#pragma once
#include <unordered_set>
#include <string>

enum class ProgrammingLanguage { CPP, JAVA, PYTHON, PHP };

enum class Gender { MALE, FEMALE };

// Программист. Знает несколько языков программирования
class Programmer {
public:
    Programmer(const std::string& name, int age, Gender gender);

    const std::string& GetName() const;
    int GetAge() const;
    Gender GetGender() const;

    void AddProgrammingLanguage(ProgrammingLanguage language);
    bool CanProgram(ProgrammingLanguage language) const;

private:
    std::string name_;
    int age_;
    Gender gender_;
    std::unordered_set<ProgrammingLanguage> programming_languages_;
};

enum class WorkerSpeciality { BLACKSMITH, CARPENTER, WOOD_CHOPPER, ENGINEER, PLUMBER };

// Рабочий. Владеет несколькими специальностями
class Worker {
public:
    Worker(const std::string& name, int age, Gender gender);

    const std::string& GetName() const;
    int GetAge() const;
    Gender GetGender() const;

    void AddSpeciality(WorkerSpeciality speciality);
    bool HasSpeciality(WorkerSpeciality speciality) const;

private:
    std::string name_;
    int age_;
    Gender gender_;
    std::unordered_set<WorkerSpeciality> specialities_;
};
