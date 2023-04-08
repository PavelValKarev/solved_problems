#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <utility>

//-Создали класс для работы с сырой памятью-//
template <typename T>
class RawMemory {
public:
    //-Конструктор и Деструктор-//
    RawMemory() = default;

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

    explicit Vector(size_t n = 0)
        : data_(n)
        , size_(n) {
        size_t i = 0;
        try {
            for (; i != n; ++i) {
                Construct(data_ + i);
            }
        }
        catch (...) {
            for (size_t j = 0; j != i; ++j) {
                Destroy(data_ + j);
            }
            throw;
        }
    }

    Vector(const Vector& other)
        : data_(other.size_)
        , size_(other.size_) {
        size_t i = 0;
        try {
            for (; i != other.size_; ++i) {
                Construct(data_ + i, other.data_[i]);
            }
        }
        catch (...) {
            for (size_t j = 0; j != i; ++j) {
                Destroy(data_ + j);
            }
            throw;
        }
    }
    ~Vector() {
        for (size_t i = 0; i != size_; ++i) {
            Destroy(data_ + i);
            
        }
        

    }

    void Reserve(size_t n) {
        if (n > data_.Capacity()) {
            //создали переменную типа RawMemory
            //передали в конструктор желаемое n
            RawMemory<T> data2(n);
            size_t i = 0;
            try {
                for (; i != size_; ++i) {
                    Construct(data2 + i, std::move(data_[i]));
                }
            }
            catch (...) {
                for (size_t j = 0; j != i; ++j) {
                    Destroy(data2 + j);
                }
                throw;
            }
            for (size_t i = 0; i != size_; ++i) {
                Destroy(data_ + i);
            }
            data_.Swap(data2);
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
