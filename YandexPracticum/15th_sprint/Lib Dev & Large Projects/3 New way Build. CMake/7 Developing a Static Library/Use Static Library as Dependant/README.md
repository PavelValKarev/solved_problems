Соберем программу шифрования изображения

В папку Cyper положим файл main.cpp + CMakeLists.txt

Рядом положим папку с файлами библиотеки ImgLib из прошлого урока + CMakeLists.txt

В файле CMake используется команда add_subdirrectory , в которой указан путь
до другой папки содержащей CMakeLists.txt , а также указана дирректория, где
будет происходить сборка библиотеки: ImgLibBuildDir 

Как запускать:
$ ./cypher.exe ./input/kitty-1-cypher.ppm ./output/kitty-1-cypher_out.ppm 123
