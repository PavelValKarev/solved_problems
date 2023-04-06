#include <memory>

using namespace std;

/*
Можно ли обернуть в unique_ptr указатель, который получен размещающим
оператором new, как показано во фрагменте? Выберите один ответ.
*/
int main() {
    alignas(Cat) char buf[sizeof(Cat)];

    unique_ptr<Cat> cat(new (&buf[0]) Cat("Luna"s, 1));
    cat->SayHello();
}

/*
Правильный ответ
Нет
Объект типа Cat создан размещающим оператором new. Чтобы удалить Cat,
нужно использовать явный вызов деструктора.
*/
