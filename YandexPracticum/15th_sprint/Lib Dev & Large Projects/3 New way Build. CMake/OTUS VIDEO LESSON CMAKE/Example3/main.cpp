#include <iostream>
#include <conio.h>

#include "version.h"

int main(int, char**) {

	std::cout << "Hello from the second CMake example!" << std::endl;
	std::cout << "Version = " << examples::getVersion() << std::endl;
	
	_getch();
	return 0;
}
