cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

set(HELLO_WORLD "Hello world")
message(STATUS "Value of HELLO_WORLD: " "${HELLO_WORLD}")

# добавляем цель hello для сборки исполняемого файла
# hello.exe под Windows, hello под Linux и macOS
# add_executable(hello src/main.cpp src/hello_printer.h src/hello_printer.cpp)
