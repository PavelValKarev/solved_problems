/*
Если потребуется выполнить иные действия при изменении удовлетворённости
человека, не нужно будет вносить изменения в класс Person. 
Достаточно создать новый класс-наследник PersonObserver и назначить его
наблюдателем:
*/

// Надсмотрщик за удовлетворённостью
class SatisfactionSupervisor : public PersonObserver {
public:
    void OnSatisfactionChanged(Person& person, int old_value, int new_value) {
        // Если уровень удовлетворённости упал слишком низко,
        // можно поднять его, вызвав person.Dance()
    }
};
