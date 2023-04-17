cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

set(HELLO_WORLD1 "Hello world1!")
set(HELLO_WORLD2 "Hello world2!")
set(HELLO_WORLD3 "Hello world3!")

string(JOIN "=/=/=/" HELLO_WORLD_JOINED "${HELLO_WORLD1}" "${HELLO_WORLD2}" "${HELLO_WORLD3}")

message(STATUS "Value of HELLO_WORLD1: " "${HELLO_WORLD1}")
message(STATUS "Value of HELLO_WORLD2: " "${HELLO_WORLD2}")
message(STATUS "Value of HELLO_WORLD3: " "${HELLO_WORLD3}")
message(STATUS "Value of HELLO_WORLD_JOINED: " "${HELLO_WORLD_JOINED}")
