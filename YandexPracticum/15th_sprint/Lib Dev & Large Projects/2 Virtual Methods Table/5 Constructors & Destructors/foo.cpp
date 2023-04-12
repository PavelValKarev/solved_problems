#include <iostream>
typedef void(*FuncPtr)();

int foo(int) {
    std::cout << "foo" << std::endl;
    return 0;
}
static FuncPtr f_p[] = { (FuncPtr)(&foo) };

int main() {
    f_p[0]();
}
