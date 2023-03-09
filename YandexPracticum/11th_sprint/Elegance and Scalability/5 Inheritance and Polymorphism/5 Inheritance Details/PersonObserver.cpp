/*
Если родительский класс не предназначен для полиморфного удаления и его экземпляры не будут
создаваться напрямую, можно избежать накладных расходов, объявив деструктор родительского
класса защищённым и невиртуальным. Так наследники этого класса будут защищены от
полиморфного удаления через указатель на базовый класс.
Например, можно ввести класс PersonObserver , который человек использует для
уведомления об изменении своего состояния. Класс Person не владеет своим наблюдателем,
поэтому деструктор PersonObserver можно сделать защищённым невиртуальным:
*/

#include <string>
#include <iostream>

using namespace std;

class Person;

// Наблюдатель за состоянием человека
class PersonObserver {
public:
    // Этот метод вызывается, когда меняется состояние удовлетворённости человека
    virtual void OnSatisfactionChanged(Person& /*person*/, int /*old_value*/, int /*new_value*/) {
        // Реализация метода базового класса ничего не делает
    }

protected:
    // Класс PersonObserver не предназначен для удаления напрямую
    ~PersonObserver() = default;
};

class Person {
public:
    Person(const string& name, int age)
        : name_(name)
        , age_(age) {
    }

    int GetSatisfaction() const {
        return satisfaction_;
    }

    string GetName() const {
        return name_;
    }

    void SetObserver(PersonObserver* observer) {
        observer_ = observer;
    }

    virtual void Dance() {
        SetSatisfaction(satisfaction_ + 1);
    }

protected:
    void SetSatisfaction(int value) {
        if (satisfaction_ != value) {
            int old_satisfaction = satisfaction_;
            satisfaction_ = value;
            // Если у человека есть наблюдатель, сообщаем ему об изменении удовлетворённости
            if (observer_) {
                observer_->OnSatisfactionChanged(*this, old_satisfaction, satisfaction_);
            }
        }
    }

private:
    string name_;
    PersonObserver* observer_ = nullptr;
    int satisfaction_ = 100;
    int age_;
};

// Шпион
class Spy : public PersonObserver {
public:
    void OnSatisfactionChanged(Person& person, int old_value, int new_value) override {
        cout << person.GetName() << "'s satisfaction has changed from "s << old_value << " to "s << new_value << endl;
    }
};

int main() {
    Person person{ "Ivan"s, 10 };

    Spy spy;
    person.SetObserver(&spy);

    person.Dance();
}
