#include <future>
#include <iostream>
#include <string_view>

#include <future>
#include <iostream>
#include <mutex>
#include <string_view>

using namespace std;

int main() {
    int i = 0;
    mutex m;
    auto f = async([&i, &m] {
        lock_guard lk{ m };
        ++i;
        });

    {
        lock_guard lk{ m };
        ++i;
    }
    f.get();
    cout << "i: "sv << i << endl;
}

/*
Данный код создает асинхронную задачу с помощью функции std::async,
которая инкрементирует переменную i, используя мьютекс m для синхронизации
доступа к переменной.

Затем в основном потоке создается объект lock_guard, который 
захватывает мьютекс m, увеличивает переменную i и освобождает мьютекс.

После этого вызывается метод get() для объекта f, чтобы дождаться
завершения асинхронной задачи.

Затем на экран выводится значение переменной i, которое в данном 
случае равно 2.

Таким образом, код демонстрирует, как использовать мьютексы для
синхронизации доступа к разделяемым данным в многопоточных приложениях.
*/
