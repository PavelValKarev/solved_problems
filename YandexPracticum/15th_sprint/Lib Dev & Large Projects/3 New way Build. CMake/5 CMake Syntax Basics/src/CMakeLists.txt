cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR src)
add_executable(hello "${SOURCE_DIR}/main.cpp" "${SOURCE_DIR}/hello_printer.h" 
               "${SOURCE_DIR}/hello_printer.cpp")
