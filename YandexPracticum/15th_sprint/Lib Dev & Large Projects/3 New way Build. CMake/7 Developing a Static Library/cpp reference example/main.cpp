#include <iostream>
#include <conio.h>
#include "structure.h"

int main() {
    int a = 5;
    int b = 8;
    int c = Sum(a, b);
    
    std::cout << a << " + " << b << " = " << c << std::endl;
	
	_getch();    
    return 0;
}
