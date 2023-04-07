#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <utility>

template <typename T>
class Vector {
public:
    size_t Size() const noexcept {
        return size_;
    }

    size_t Capacity() const noexcept {
        return capacity_;
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < size_);
        return data_[index];
    }

    explicit Vector(size_t n = 0) {
        //резервируем сырую память в необходимом объеме
        //сохранить то что получилось в поле data
        data_ = Allocate(n);
        //в этой памяти не было сконструировано ни одного эл-а
        //памятью мы владеем, но эл-ов там нет
        //Создаем n эл-ов в этой памяти
        for (size_t i = 0; i !=n; ++i) {
            //конструирую эл-т в очередной ячейке, которая
            //получается из указателя сдвигом на i
            Construct(data_ + i);
        }
        capacity_ = size_ = n;
    }

    //конструктор копирования пишется аналогично
    //разница в том, что задан не n, а другой образец
    Vector(const Vector& other) {
        data_ = Allocate(other.size_);
        for (size_t i = 0; i != other.size_; ++i) {
            //здесь мы берем i-й эл-т другого вектора
            Construct(data_ + i, other[i]);
        }
        capacity_ = size_ = other.size_;
    }
    ~Vector() {
        //сначала нужно вручную удалить все эл-ы которые
        //хранились в этом векторе, а потом требуется вернуть 
        //память операционной системе
        for (size_t i = 0; i != size_; ++i) {
            //у каждого из них вызываем Destroy
            Destroy(data_ + i);
        }
        Deallocate(data_);
    }

    void Reserve(size_t n) {
        //должна резервировать память под n-будущих эл-ов
        //сначала нужно сравнить это n с нашей емкостью
        if (n > capacity_) {
            //резервируем память в другом месте
            auto data2 = Allocate(n);
            //после этого в цикле скопируем вектор
            for (size_t i = 0; i!= size_ ; ++i) {
                //используем move для перемещения объекта
                Construct(data2 + i, std::move(data_[i]));
                //удалим объект из старого места, т.к. мы 
                //его уже переместили
                Destroy(data_ + i);
            }
            //вызываем Deallocate на текущие данные
            Deallocate(data_);
            //и заменяем наши данные новыми
            data_ = data2;
            //настраиваем переменную емкости = n
            capacity_ = n;
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
    T* data_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;

    //вспомогательные статические ф-ии резервирования сырой памяти
    
    //получает на вход кол-во элементов
    static T* Allocate(size_t n) {
        //вызывает operator new резервирующий кол-во байт
        //ф-я должна вернуть не void а указатель на T 
        return static_cast<T*>(operator new (n * sizeof(T))) ;
    }

    //получает на вход буффер
    static void Deallocate(T * buf) {
        //вызывает operator delete от этого буфера
        operator delete(buf);
    }

    static void Construct(void * buf) {
        //в этом месте памяти конструирует объект по умолчанию
        //просто вызывает размещающий опреатор new
        new (buf) T();

    }

    //удобно иметь несколько перегруженных ф-й, когда на вход
    //подается какой-то объект, к которому нужно применить конструктор
    //копирования
    static void Construct(void* buf, const T& elem ) {
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
