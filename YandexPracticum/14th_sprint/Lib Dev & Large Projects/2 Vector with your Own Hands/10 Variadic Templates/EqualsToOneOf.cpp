#include <cassert>
#include <string>
#include <string_view>

using namespace std;

/*
Напишите шаблонную функцию EqualsToOneOf, которая возвращает true, когда её
первый аргумент равен хотя бы одному из последующих аргументов. В остальных
случаях функция должна возвращать false. Если в функцию был передан только
один параметр, она должна возвращать false.
*/

template<typename ... T>
bool EqualsToOneOf(const T& ... values){
    //если в функцию был передан только один пар-р
    //то она должна возвращать false
    if (sizeof...(values) == 1) {
        return false;
    }
}

template<typename T1, typename T2, typename ... Ts>
bool EqualsToOneOf(const T1& first, const T2& second, const Ts& ... args) {
  return (first == second) || EqualsToOneOf(first, args...);  
}

int main() {
    assert(EqualsToOneOf("hello"sv, "hi"s, "hello"s));
    assert(!EqualsToOneOf(1, 10, 2, 3, 6));
    assert(!EqualsToOneOf(8));
}
