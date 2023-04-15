cmake_minimum_required(VERSION 3.5)

project(Example2)

#possible var1:
# #add_executable(version.exe main.cpp version.cpp)

#also possible var2:
#version.h will be in project tree, ot is more friendly 
#add_executable(version.exe main.cpp version.h version.cpp)


#more representative var3:

set (SOURCES
	main.cpp
	version.cpp
)

set (HEADERS
	version.h
)

add_executable(version ${SOURCES} ${HEADERS})

set_target_properties(
		version PROPERTIES
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED ON
)
