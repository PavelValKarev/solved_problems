class Person {
public:
    ...
        // Реализация виртуального метода может быть переопределена в классах-наследниках
        virtual void Dance() const {
        cout << name_ << " is dancing"s << endl;
    }

private:
    string name_;
    int age_;
};
