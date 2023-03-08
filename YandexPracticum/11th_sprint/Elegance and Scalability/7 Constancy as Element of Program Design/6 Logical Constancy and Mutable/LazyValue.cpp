#include <cassert>
#include <functional>
#include <string>
#include <optional>
#include <mutex>

using namespace std;

template <typename T>
class LazyValue {
public:
    explicit LazyValue(function<T()> init) 
        : init_(std::move(init)) {
    }

    bool HasValue() const {
        if (value) {
            return true;
        }
        else return false;
    }
    const T& Get() const {
        if (lock_guard g(m);  !HasValue()) {
            value = init_();
        }
        return *value;
    }

private:
    std::function<T()> init_;
    mutable std::optional<T> value;
    mutable mutex m;
};

void UseExample() {
    const string big_string = "Giant amounts of memory"s;

    LazyValue<string> lazy_string([&big_string] {
        return big_string;
        });

    assert(!lazy_string.HasValue());
    assert(lazy_string.Get() == big_string);
    assert(lazy_string.Get() == big_string);
}

void TestInitializerIsntCalled() {
    bool called = false;

    {
        LazyValue<int> lazy_int([&called] {
            called = true;
            return 0;
            });
    }
    assert(!called);
}

int main() {
    UseExample();
    TestInitializerIsntCalled();
}

/*
Задание
Иногда на практике встречаются объекты, создание которых занимает значительное время, при этом они нужны не при каждом запуске программы. Например, клиент системы контроля версий может обращаться к локальным файлам, а может — к удалённому репозиторию. Тогда устанавливать соединение с удалённым репозиторием можно, только если пользователь решил к нему обратиться.
Для представления таких объектов может быть полезен шаблон LazyValue<T>. У него есть константный метод const T& Get(), который возвращает ссылку на созданный объект. В своём конструкторе LazyValue принимает инициализирующую функцию, которая используется при первом вызове метода Get для создания хранимого объекта. Последующие вызовы Get просто возвращают ссылку на хранимый объект.
Таким образом, объект класса LazyValue<T> не тратит время на создание хранимого объекта до первого вызова метода Get.
Вам дан интерфейс шаблона LazyValue. Реализуйте его.
Инициализирующая функция передаётся в LazyValue через объект класса function<T>. Это удобная обёртка, позволяющая передавать любые объекты, к которым можно применить operator(), то есть объект этого типа может быть вызван как обычная функция.
Интерфейс шаблона приведён в заготовке кода.
Ограничения

Объект класса LazyValue<T> не должен конструировать объект типа T при своём создании.
При первом вызове метода LazyValue<T>::Get должен создаваться объект типа T с помощью функции, переданной в конструктор LazyValue<T>.
Последующие вызовы метода Get не должны вызывать функцию, переданную в конструктор.
Если за время жизни объекта LazyValue<T> метод Get не был вызван ни разу, то инициализирующая функция не должна быть вызвана.
Шаблон LazyValue должен поддерживать работу с типами без конструктора по умолчанию.

*/
