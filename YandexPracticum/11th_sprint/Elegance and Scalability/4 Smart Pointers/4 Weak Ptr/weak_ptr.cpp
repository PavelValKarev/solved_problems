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

int main() {
    auto sp = make_shared<Object>();

    weak_ptr wp{ sp };  // Аналог weak_ptr<Object> wp{sp};

    // Пока объект жив, слабые ссылки не устаревают
    assert(!wp.expired());
    // После обнуления shared_ptr объект удаляется
    sp.reset();

    // С этого момента все слабые ссылки становятся устаревшими
    assert(wp.expired());
}

/*
Встречайте, weak_ptr!
std::weak_ptr — умный указатель, хранящий невладеющую, или слабую,
ссылку на объект, на который ссылается shared_ptr.
weak_ptr позволяет безопасно узнать, существует ли объект, на
который он ссылается, и получить к нему временный доступ, если
объект всё ещё жив. При этом наличие слабой ссылки не продлевает
объекту жизнь. Объект будет удалён, как только на него перестанут
ссылаться shared_ptr, — по этой причине их ещё называют сильными
ссылками:
*/
