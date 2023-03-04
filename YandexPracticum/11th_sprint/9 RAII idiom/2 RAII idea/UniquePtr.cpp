#include <cassert>
#include <algorithm>
#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* ptr_;
public:
    //Конструктор по умолчанию, создающий пустой умный указатель.
    UniquePtr() {
        ptr_ = nullptr;
    };
    //Конструктор, принимающий T* и захватывающий владение этой динамической памятью.
    explicit UniquePtr(T* ptr): ptr_(ptr) {}
    UniquePtr(const UniquePtr&) = delete;
    //Конструктор перемещения, получающий на вход rvalue - ссылку на другой
    //UniquePtr и отбирающий у него владение ресурсом.
    UniquePtr(UniquePtr&& other) : ptr_(move(other.ptr_)) {
        ptr_ = move(other.ptr_);
        other.ptr_ = nullptr;
    }
    UniquePtr& operator=(const UniquePtr&) = delete;
    //Оператор присваивания, получающий на вход nullptr (тип - nullptr_t, определенный
    //в заголовочном файле cstddef).В результате умный указатель должен стать пустым.
    UniquePtr& operator=(nullptr_t) {
        delete ptr_;
        ptr_ = nullptr;
        return *this;
    }
    //Move-оператор присваивания, получающий на вход rvalue-ссылку на другой UniquePtr.
    UniquePtr& operator=(UniquePtr&& other) {
        delete ptr_;
        ptr_ = move(other.ptr_);
        other.ptr_ = nullptr;
        return *this;
    }
    //Деструктор.
    ~UniquePtr() {
        delete ptr_;
    }
    //Оператор *.
    T& operator*() const{
        return *ptr_;
    }
    //Оператор -> — он должен вернуть указатель на обычную структуру, к которой
    //можно применить обычный ->.
    T* operator->() const {
        return ptr_;
    }
    //Функцию T* Release() — она отменяет владение объектом и возвращает
    //хранящийся внутри указатель.
    T* Release() {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }
    //Функцию void Reset(T* ptr), после выполнения которой умный
    //указатель должен захватить ptr.
    void Reset(T* ptr) {
        delete ptr_;
        ptr_ = ptr;
    }
    //Функцию void Swap(UniquePtr& other), обменивающуюся содержимым
    //с другим умным указателем.
    void Swap(UniquePtr& other) {
        swap(ptr_, other.ptr_);
    }
    //Функцию T* Get() const, возвращающую указатель.
    T* Get() const {
        return ptr_;
    }
};

struct Item {
    static int counter;
    int value;
    Item(int v = 0)
        : value(v)
    {
        ++counter;
    }
    Item(const Item& other)
        : value(other.value)
    {
        ++counter;
    }
    ~Item() {
        --counter;
    }
};

int Item::counter = 0;

void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        assert(Item::counter == 1);

        ptr.Reset(new Item);
        assert(Item::counter == 1);
    }
    assert(Item::counter == 0);

    {
        UniquePtr<Item> ptr(new Item);
        assert(Item::counter == 1);

        auto rawPtr = ptr.Release();
        assert(Item::counter == 1);

        delete rawPtr;
        assert(Item::counter == 0);
    }
    assert(Item::counter == 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    assert(ptr.Get()->value == 42);
    assert((*ptr).value == 42);
    assert(ptr->value == 42);
}

int main() {
    TestLifetime();
    TestGetters();
}
