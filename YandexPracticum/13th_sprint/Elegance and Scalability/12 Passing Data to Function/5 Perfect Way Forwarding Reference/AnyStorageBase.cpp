#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <memory>

using namespace std;

//определяем абстрактный базовый класс AnyStorageBase, который содержит 
//виртуальный деструктор и виртуальный метод Print().
//он явлается родительским для класса AnyStorage, который является
//шаблонным классом
class AnyStorageBase {
public:           
    virtual void Print(std::ostream& out) const = 0;
    virtual ~AnyStorageBase() {}
};

//Класс AnyStorage - это хранилище с удаленным типом для объектов
//любого типа. Он имеет единственный элемент данных data_ типа T,
//который является объектом, подлежащим хранению. У него также есть
//конструктор, который пересылает свой аргумент любого типа конструктору data_.

template <typename T>
class AnyStorage : public AnyStorageBase {
public:
    // конструктор AnyStorage, принимающий T универсальным образом
    template<typename S>
    AnyStorage(S&& data): data_(std::forward<S>(data)){}

    void Print(ostream& out) const override {
        out << data_;
    }

private:
    T data_;
};

/*
Наконец, класс Any содержит единственный элемент данных data_ типа
unique_ptr<AnyStorageBase>. Его конструктор пересылает свой аргумент
конструктору AnyStorage<T>, где T - тип аргумента. Метод печати Any
вызывает метод печати объекта AnyStorageBase, хранящегося в data_. 
Деструктор Any удаляет объект AnyStorageBase, хранящийся в data_.
*/
class Any {
public:  
    
    template<typename T>
    Any(T&& data)
        : storage_(new AnyStorage<std::remove_reference_t<T>>(std::forward<T>(data))){}

    void Print(std::ostream& out) const {
        storage_->Print(out);
    }
private:
    unique_ptr<AnyStorageBase> storage_;
};

class Dumper {
public:
    Dumper() {
        std::cout << "construct"sv << std::endl;
    }
    ~Dumper() {
        std::cout << "destruct"sv << std::endl;
    }
    Dumper(const Dumper&) {
        std::cout << "copy"sv << std::endl;
    }
    Dumper(Dumper&&) {
        std::cout << "move"sv << std::endl;
    }
    Dumper& operator=(const Dumper&) {
        std::cout << "= copy"sv << std::endl;
        return *this;
    }
    Dumper& operator=(Dumper&&) {
        std::cout << "= move"sv << std::endl;
        return *this;
    }
};

ostream& operator<<(ostream& out, const Any& arg) {
    arg.Print(out);
    
    return out;
}

ostream& operator<<(ostream& out, const Dumper&) {
    return out;
}

int main() {
    Any any_int(42);
    Any any_string("abc"s);

    // операция вывода Any в поток определена чуть выше в примере
    cout << any_int << endl << any_string << endl;

    Any any_dumper_temp{ Dumper() };

    Dumper auto_dumper;
    Any any_dumper_auto(auto_dumper);
}
