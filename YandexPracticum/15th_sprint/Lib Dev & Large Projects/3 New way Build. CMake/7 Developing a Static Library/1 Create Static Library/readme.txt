В папку ImgLib положим 4 файла 
img_lib.h
img_lib.cpp
ppm_image.h
ppm_image.cpp

+ CMakeLists.txt

Вместо add_executable цесль создается командой add_library с параметором STATIC
В списке исходных файлов отсутствует main.cpp

Создадим рядом папку build и в ней выполним команды
cmake ../ImgLib -G "Eclipse CDT4 - MinGW Makefiles"-DCMAKE_BUILD_TYPE=Debug
cmake --build . --verbose
