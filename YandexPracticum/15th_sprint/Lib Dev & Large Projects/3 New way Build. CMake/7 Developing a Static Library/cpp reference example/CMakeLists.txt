# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(my_project)

# Добавляем библиотеку
add_library(my_lib STATIC structure.cpp)

# Добавляем путь к заголовочным файлам
target_include_directories(my_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Создаем исполняемый файл
add_executable(main main.cpp)

# Линкуем исполняемый файл с библиотекой
target_link_libraries(main my_lib)



