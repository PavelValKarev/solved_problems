// hello_printer.cpp
#include <iostream>
#include <string_view>

using namespace std;

void PrintHelloCMake() {
	using namespace std::literals::string_literals;
	std::cout << "Hello, CMake!"sv << std::endl;
}
