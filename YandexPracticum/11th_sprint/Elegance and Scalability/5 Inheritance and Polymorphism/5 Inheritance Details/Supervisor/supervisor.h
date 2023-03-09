
#pragma once

#include "people.h"
/*
    Надзиратель за уровнем удовлетворённости.
    Способен наблюдать за состоянием человека
    Если уровень удовлетворённости человека опустится ниже минимального уровня, Надзиратель
    побуждает человека танцевать до тех пор, пока уровень уровень удовлетворённости
    не станет больше или равен максимальному значению
*/
class SatisfactionSupervisor: public PersonObserver {
    int minSat, maxSat;
public:
    // Конструктор принимает значение нижнего и верхнего уровня удовлетворённости
    SatisfactionSupervisor(int min_satisfaction, int max_satisfaction)
        : minSat(min_satisfaction), maxSat(max_satisfaction) {
        // Напишите реализацию самостоятельно
    }
    
    void OnSatisfactionChanged(Person& p, int prevSat, int newSat) override
    {
        if(newSat > prevSat)
            return;
        if(newSat < minSat)
        {
            while(p.GetSatisfaction() < maxSat)
                p.Dance();
        }
    }

    ~SatisfactionSupervisor() override
    {
        
    }
};
