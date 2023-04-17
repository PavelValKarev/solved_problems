cmake_minimum_required(VERSION 3.11)
project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

set(HELLO_WORLD "Hello world!" "Hello world2!")

list(JOIN HELLO_WORLD " " HELLO_WORLD_JOINED)

message(STATUS "Value of HELLO_WORLD: " "${HELLO_WORLD}")
message(STATUS "Value of HELLO_WORLD_JOINED: " "${HELLO_WORLD_JOINED}")
