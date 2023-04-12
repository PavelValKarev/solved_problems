#include <iostream>
class A;
struct VTable
{
    void (*say_hello)(A*);
};
class A
{
public:
    A()
    {
        vtable.say_hello = A::sayHello;
    }

    void sayHello()
    {
        vtable.say_hello(this);
    }
    static void sayHello(A* a)
    {
        std::cout << "A::sayHello" << std::endl;
    }
    VTable vtable;
};
class B
{
public:
    B()
    {
        a.vtable.say_hello = B::sayHello;
    }
    void sayHello()
    {
        a.vtable.say_hello((A*)this);
    }
    static void sayHello(A* a)
    {
        std::cout << "B::sayHello\n" << std::endl;
    }
private:
    A a;
};

int main()
{
    A* a = (A*)(new B);
    a->sayHello();
    delete a;
}
