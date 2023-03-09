#include "people.h"

#include <stdexcept>

using namespace std;

const string& Person::GetName() const {
    return name_;
}

int Person::GetAge() const {
    
    return age_;
}

Gender Person::GetGender() const {
    
    return gender_;
}

void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {
    langs.push_back(language);
}

bool Programmer::CanProgram(ProgrammingLanguage language) const {
    
    return std::find(langs.begin(), langs.end(), language) != langs.end();
}

void Worker::AddSpeciality(WorkerSpeciality speciality) {
    specs.push_back(speciality);
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {
    // Заглушка, реализуйте метод самостоятельно
    return std::find(specs.begin(), specs.end(), speciality) != specs.end();

}
