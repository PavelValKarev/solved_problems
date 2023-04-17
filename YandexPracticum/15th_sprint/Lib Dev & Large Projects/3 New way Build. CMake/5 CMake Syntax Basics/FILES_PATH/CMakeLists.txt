cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR src)
set(FILES_PRINTER "${SOURCE_DIR}/hello_printer.h" "${SOURCE_DIR}/hello_printer.cpp")
set(FILES_MAIN "${SOURCE_DIR}/main.cpp")
add_executable(hello ${FILES_PRINTER} ${FILES_MAIN})
