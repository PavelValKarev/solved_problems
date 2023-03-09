#pragma once

#include <string>

class Person;

// Наблюдатель за состоянием человека.
class PersonObserver {
public:
    // Этот метод вызывается, когда меняется состояние удовлетворённости человека
    virtual void OnSatisfactionChanged(Person& /*person*/, int /*old_value*/, int /*new_value*/) {
        // Реализация метода базового класса ничего не делает
    }

protected:
    // Класс PersonObserver не предназначен для удаления напрямую
    virtual ~PersonObserver() = default;
};

/*
    Человек.
    При изменении уровня удовлетворённости уведомляет
    связанного с ним наблюдателя
*/
class Person {
public:
    Person(const std::string& name, int age): name_(name), age_(age), danceCount_(0) {
        
    }

    int GetSatisfaction() const {
        return satisfaction_;
    }

    const std::string& GetName() const {
        return name_;
    }

    // «Привязывает» наблюдателя к человеку. Привязанный наблюдатель
    // уведомляется об изменении уровня удовлетворённости человека
    // Новый наблюдатель заменяет собой ранее привязанного
    // Если передать nullptr в качестве наблюдателя, это эквивалентно отсутствию наблюдателя
    virtual void SetObserver(PersonObserver* observer) {
        observer_ = observer;
    }

    int GetAge() const {
        return age_;
    }

    // Увеличивает на 1 количество походов на танцы
    // Увеличивает удовлетворённость на 1
    virtual void Dance() {
        danceCount_+=1;
        ChangeSatisfaction(1);
    }

    int GetDanceCount() const {
        
        return danceCount_;
    }

    // Прожить день. Реализация в базовом классе ничего не делает
    virtual void LiveADay() {
        // Подклассы могут переопределить этот метод
    }

    virtual ~Person()
    {
        
    }
    
private:
    std::string name_;
    
    int satisfaction_ = 100;
    int age_;
    
protected:
    int danceCount_;
    PersonObserver* observer_ = nullptr;
    void ChangeSatisfaction(int s)
    {
        satisfaction_+=s;
        if(observer_)
            observer_->OnSatisfactionChanged(*this, satisfaction_ - s, satisfaction_);
        
    }
};

// Рабочий.
// День рабочего проходит за работой
class Worker: public Person {
    int workDone_ = 0;
    
public:
    Worker(const std::string& name, int age):Person(name, age) {
        // Напишите недостающий код
    }
    void SetObserver(PersonObserver* observer) override {
        observer_ = observer;
    }
    // Рабочий старше 30 лет и младше 40 за танец получает 2 единицы удовлетворённости вместо 1

    // День рабочего проходит за работой

    // Увеличивает счётчик сделанной работы на 1, уменьшает удовлетворённость на 5
    void Work() {
        workDone_ += 1;
        ChangeSatisfaction(-5);
    }

    // Возвращает значение счётчика сделанной работы
    int GetWorkDone() const {
        
        return workDone_;
    }
    
    void LiveADay() override
    {
        Work();
    }
    
    void Dance() override {
        danceCount_+=1;
        if (GetAge() > 30 && GetAge() < 40)
        {
            ChangeSatisfaction(2);
        }else
        {
            ChangeSatisfaction(1);
        }
    }
    ~Worker() override
    {
        
    }
    
};

// Студент.
// День студента проходит за учёбой
class Student: public Person {
    int knowledge_ = 0;
public:
    Student(const std::string& name, int age):Person(name, age) {
        // Напишите недостающий код
    }
    void SetObserver(PersonObserver* observer) override {
        observer_ = observer;
    }
    // День студента проходит за учёбой

    // Учёба увеличивает уровень знаний на 1, уменьшает уровень удовлетворённости на 3
    void Study() {
        knowledge_ += 1;
        ChangeSatisfaction(-3);
    }
    
    // Возвращает уровень знаний
    int GetKnowledgeLevel() const {
        return knowledge_;
    }
    
    void LiveADay() override
    {
        Study();
    }
    ~Student() override
    {
        
    }
    
};
