class Worker : public Person {
public:
    ...
        // Метод Dance переопределяет (override) реализацию базового класса
        void Dance() const override {
        // Сначала вызываем метод Dance родительского класса
        Person::Dance();
        // Добавляем дополнительное поведение
        cout << "Oppa!"s << endl;
    }

private:
    WorkerSpeciality speciality_;
};

/*

*/
