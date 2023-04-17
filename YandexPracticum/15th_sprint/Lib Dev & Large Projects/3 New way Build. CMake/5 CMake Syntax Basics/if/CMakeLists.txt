cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

if(MY_BEAUTIFUL_VARIABLE)
    message(STATUS "MY_BEAUTIFUL_VARIABLE exists and equals ${MY_BEAUTIFUL_VARIABLE}")
else()
    message(STATUS "MY_BEAUTIFUL_VARIABLE does not exist or equals OFF. Miss it.")
endif()
