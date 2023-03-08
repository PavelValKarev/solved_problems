#include <memory>
#include <iostream>
#include <string>

using namespace std;

#include <cassert>
#include <memory>

using namespace std;

struct Object {
    void DoSomething() {
    }
};

/*
Чтобы безопасно обратиться к объекту, на который ссылается weak_ptr, нужно получить временный
объект shared_ptr, используя метод lock. Если объект был удалён, метод lock вернёт нулевой указатель:
*/

int main() {
    auto sp = make_shared<Object>();
    weak_ptr wp{ sp };

    if (auto sp2 = wp.lock()) {
        // В этом блоке можно безопасно обращаться к объекту, используя сильную ссылку
        sp2->DoSomething();
    }
    else {
        // Сюда мы не попадём, так как на объект всё ещё ссылается sp
        assert(false);
    }

    sp.reset();
    // Объект уже разрушен, создать сильную ссылку не выйдет
    assert(!wp.lock());
}

