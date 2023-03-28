#include <iostream>

class MyClass {
public:
    static int staticMethod(int x, int y) {
        return x + y;
    }
};

int main() {
  
  //статический метод можно вызывать без создания 
  //экземпляра класса
    int result = MyClass::staticMethod(3, 4);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
