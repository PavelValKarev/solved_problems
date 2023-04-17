cmake_minimum_required(VERSION 3.11)

project(HelloCMake CXX)
set(CMAKE_CXX_STANDARD 17)

set(VAR1 15)
set(VAR2 3)
set(VAR15 "Pussy")
message(STATUS "${VAR${VAR1}} ${VAR${VAR2}}cat")
