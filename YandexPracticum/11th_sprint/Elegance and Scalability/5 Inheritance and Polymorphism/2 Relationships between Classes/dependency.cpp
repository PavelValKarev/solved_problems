// Поставщик. Предоставляет функционал, нужный Клиенту
class Supplier { 
public:
    void DoSomething();
    ...
};

// Клиент. Использует функционал, предоставляемый ему Поставщиком
class Client {
public:
    // Зависимость передаётся через параметр метода
    void DependentMethod1(Supplier& supplier) {
        supplier.DoSomething();
    }

    // Клиент создаёт экземпляр Поставщика и использует его
    void DependentMethod2() {
        Supplier supplier;
        supplier.DoSomething();
    }

    // Клиент возвращает Поставщика
    Supplier DependentMethod3() {
        return Supplier{};
    }

    // Этот метод не зависит от Поставщика
    void IndependentMethod() {
        cout << "Hello"s << endl;
    }
};
