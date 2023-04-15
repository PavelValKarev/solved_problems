cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

# добавляем цель hello для сборки исполняемого файла
# hello.exe под Windows, hello под Linux и macOS
add_executable(negate main.cpp img_lib.h img_lib.cpp ppm_image.cpp ppm_image.cpp)
