#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <utility>
#include <memory>
#include <algorithm>

//-Создали класс для работы с сырой памятью-//
template <typename T>
class RawMemory {
public:
    RawMemory() = default;
    //запрет конструктора копирования, не имеет смысла для сырой памяти
    RawMemory(const RawMemory&) = delete;
    //Оператор присваивания также запрещаем
    RawMemory& operator = (const RawMemory&) = delete;

    //Оператор присваивания, у которого в правой части стоит
    //временный объект - вполне уместен, т.к. у такого объекта
    //можно отобрать владение
    RawMemory& operator = (RawMemory&& other) noexcept {
        //здесь мы владеем тем, что пришло к нам во временном объекте
        Swap(other);
        //а для другой части предполагаем, что скоро будет вызван деструктор
        //ну и любой оператор присваивания возвращает ссылку на себя
        return *this;
    }


    //самый простой способ сделать конструктор временного объекта
    //это воспользоваться ф-ей Swap
    RawMemory(RawMemory&& other) noexcept {
        //other станет объектом с нулевыми значениями capacity_
        //и data_=nullptr заданными по умолчанию
        //а мы завладеем тем объектом, который был other
        Swap(other);
    }

    RawMemory(size_t capacity)
        : buffer_(Allocate(capacity))
        , capacity_(capacity) {
    }

    ~RawMemory() {
        Deallocate(buffer_);
    }

    //-Функцииии для работы с сырой памятью-//
    // Выделяет сырую память под n элементов и возвращает указатель на неё
    static T* Allocate(size_t n) {
        //вызывает operator new резервирующий кол-во байт
        //ф-я должна вернуть не void а указатель на T 
        return n != 0 ? static_cast<T*>(operator new(n * sizeof(T))) : nullptr;
    }
    // Освобождает сырую память, выделенную ранее по адресу buf при помощи Allocate
    static void Deallocate(T* buffer_) noexcept {
        //вызывает operator delete от этого буфера
        operator delete(buffer_);
    }

    //-перегрузка операторов для упрощения класса Vector-//
    T* operator + (size_t offset) {
        // Разрешается получать адрес ячейки памяти, следующей за последним элементом массива
        assert(offset <= capacity_);
        return buffer_ + offset;
    }

    const T* operator+(size_t offset) const noexcept {
        return const_cast<RawMemory&>(*this) + offset;
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<RawMemory&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < capacity_);
        return buffer_[index];
    }

    //-Swap-//
    void Swap(RawMemory& other) noexcept {
        std::swap(buffer_, other.buffer_);
        std::swap(capacity_, other.capacity_);
    }

    const T* GetAddress() const noexcept {
        return buffer_;
    }

    T* GetAddress() noexcept {
        return buffer_;
    }

    size_t Capacity() const {
        return capacity_;
    }

private:
    //-Перенесли поля из класса вектор-//
    T* buffer_ = nullptr; //указатель на данные
    size_t capacity_ = 0;
};

template <typename T>
class Vector {
public:
    size_t Size() const noexcept {
        return size_;
    }

    size_t Capacity() const noexcept {
        return data_.Capacity();
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < size_);
        return data_[index];
    }

    //написали конструктор по умолчанию
    Vector() = default;

    //убрали значение по умолчанию пар-ра n
    explicit Vector(size_t n)
        : data_(n)
        , size_(n) {
        //ф-я создания эл-ов, у нее уже два аргумента
        //где создавать и сколько штук
        std::uninitialized_value_construct_n(
            data_.GetAddress(), n
        );
    }

    Vector(const Vector& other)
        : data_(other.size_)
        , size_(other.size_) {
        //использую стандартную функцию для копирования
        //неинициализированной памяти. Сперва указываю
        //откуда копировать и сколько эл-ов, а потом - куда
        std::uninitialized_copy_n(
            other.data_.GetAddress(), other.size_, data_.GetAddress()
        );
    }

    void Swap(Vector& other) noexcept {
        data_.Swap(other.data_);
        std::swap(size_, other.size_);
    }

    Vector(Vector&& other) {
        Swap(other);
    }

    ~Vector() {
        std::destroy_n(data_.GetAddress(), Size());
    }

    //копирующий оператор присваивания
    Vector& operator = (const Vector& other) {
        if (other.Size() > data_.Capacity()) {
            Vector tmp(other);
            Swap(tmp);
            return *this;
        }
        //если наша емкость позволяет вместить все эл-ы, которые
        //стоят справа, то давайте ее переиспользовать
        else {
            //запустим цикл, который пройдет до минимального из размеров
            for (size_t i = 0; i < Size() && i < other.Size(); ++i) {
                //перезапись значения при помощи оператора присваивания
                data_[i] = other[i];
            }
            if (Size() < other.Size()) {
                //добавим недостающие эл-ы в сырую память после уже имеющихся
                std::uninitialized_copy_n(
                    //копируем отсюда вычисляя размер
                    other.data_.GetAddress() + Size(),
                    other.Size() - Size(),
                    //копируем в нашу сырую память начиная с нужного места
                    data_.GetAddress() + Size()
                );
            } else if (Size() > other.Size()) {
                //удаляем лишние элементы
                std::destroy_n(
                    //на вход подаем начало буфера где эти эл-ы хранятся
                    data_.GetAddress() + other.Size(),
                    //и их кол-во = разность размеров из большего меньший
                    Size() - other.Size()
                );
            }
            //не забыть поменять размер вектора на новый
            size_ = other.Size();
        }
        return *this;
    }

    Vector& operator = (Vector&& other) noexcept {
        Swap(other);
        return *this;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > data_.Capacity()) {
            //создали переменную типа RawMemory            
            RawMemory<T> new_data(new_capacity);

            /*
            Задумаемся. Вместо конструктора копирования зачастую лучше использовать конструктор перемещения
            Эта конструкция будет работать, если конструктор перемещения не генерирует исключений
            constexpr оператор if будет вычислен во время компиляции
            Шаблоны std::is_copy_constructible_v и std::is_nothrow_move_constructible_v помогают узнать,
            есть ли у типа копирующий конструктор и noexcept-конструктор перемещения.
            Наивное решение if-else работать не будет
            Чтобы решить проблему, нужно использовать if constexpr. Это версия оператора if, которая
            выполняется во время компиляции. Выражение в условии должно быть константой времени компиляции.
            В итоге скомпилируется только одна из двух веток, что и требуется:
            */
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(data_.GetAddress(), size_, new_data.GetAddress());
            }
            else {
                std::uninitialized_copy_n(data_.GetAddress(), size_, new_data.GetAddress());
            }
            //стандартная ф-я вызывающая деструкторы
            std::destroy_n(data_.GetAddress(), Size());
            data_.Swap(new_data);
        }
    }

    /*Vector(Vector&& other);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    void Resize(size_t n);
    void PushBack(const T& elem);
    void PushBack(T&& elem);
    void PopBack();
    T& EmplaceBack();*/

private:
    RawMemory<T> data_;
    size_t size_ = 0;

    static void Construct(void* buf) {
        //в этом месте памяти конструирует объект по умолчанию
        //просто вызывает размещающий опреатор new
        new (buf) T();
    }

    //удобно иметь несколько перегруженных ф-й, когда на вход
    //подается какой-то объект, к которому нужно применить конструктор
    //копирования
    static void Construct(void* buf, const T& elem) {
        new (buf) T(elem);
    }

    //для временного объекта
    static void Construct(void* buf, const T&& elem) {
        new (buf) T(std::move(elem));
    }

    static void Destroy(T* buf) {
        //просто вызываем деструктор
        buf ->~T();
    }
};
