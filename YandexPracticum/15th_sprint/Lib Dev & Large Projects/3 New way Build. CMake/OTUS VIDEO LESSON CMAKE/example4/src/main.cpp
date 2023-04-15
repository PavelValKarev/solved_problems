#include "config.h"
#include "lib.h"

#include <iostream>
#include <conio.h>

int main(int, char**) {

	std::cout << "Hello from main!" << std::endl;
	lib::makeSomeSuperJob();
	std::cout << "Lib version: " << lib::getVersion() << std::endl;
	
	std::cout << "Main version: " << PROJECT_VERSION << std::endl;
	
	_getch();
	return 0;
}
