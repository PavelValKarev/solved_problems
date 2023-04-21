cmake_minimum_required(VERSION 3.11)

#задает стандарт cpp
project(HelloCMAKE CXX)
#задаем значение переменной, показывая С++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#target_link_libraries(negate -lstdc++)

#добавляем цель hello
#для создания исполняемого файла нужно собщить название цели
#и список файлов исходного кода
add_executable(hello.exe src/main.cpp src/hello_printer.h src/hello_printer.cpp)
