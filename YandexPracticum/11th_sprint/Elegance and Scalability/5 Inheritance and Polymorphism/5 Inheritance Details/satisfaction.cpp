// Example1_PersonWorker.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

class Person {

public:
    //параметризованный конструктор
    Person(const string& name, int age)
        : name_(name)
        , age_(age) {
    }

    int GetAge() const {
        return age_; 
    }
    
    const string& GetName() const {
        return name_; 
    }
    
    virtual void Dance() {
        ++satisfaction_;
    }

    int GetSatisfaction() const {
        return satisfaction_;
    }

protected: //уровень удовлетворения теперь доступен наследникам класса Person
    void SetSatisfaction(int value) {
        satisfaction_ = value;
    } 
private:
    string name_;
    int age_;
    int satisfaction_ = 100;
};

class Worker : public Person {
public:
    
    explicit Worker(string name, int age)
        //в списке инициализации вызываем параметризованный конструктор класса-родителя
        : Person(name, age) {
    }
    
    void Dance() override {
        //Рабочий сперва просто танцует как обычный человек
        Person::Dance();

        //Рабочий в возрасте от 30 до 40 во время танца получает
        //дополнительную порцию удовлетворения +1
        if (const int age = GetAge(); age > 30 && age < 45) {
            cout << "Oppa!" << endl;
            SetSatisfaction(GetSatisfaction()+1);
        }
    }

    void Work() {
        //работа уменьшает удовлетворенность на 1
        SetSatisfaction(GetSatisfaction() - 1);
    }
private:
    //WorkerSpeciality speciality_;
};

int main() {
    //using namespace string_literals;
    Worker Stepan("Stepan"s, 23);
    Stepan.Dance();
    cout << "Stepan after dance: " << Stepan.GetSatisfaction() << endl;
    Stepan.Work();
    cout << "Stepan after work: " << Stepan.GetSatisfaction() << endl;
    Worker Pavel("Pavel"s, 43);
    Pavel.Dance();
    cout << "Pavel after dance: " << Pavel.GetSatisfaction() << endl;
    Pavel.Work();
    cout << "Pavel after work: " << Pavel.GetSatisfaction() << endl;
   
    return 0;
}


