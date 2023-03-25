#include <iostream>
#include <fstream>

int main() {
    // Создаем поток ввода и открываем файл "example.bin" в бинарном режиме
    std::ifstream input("example.bin", std::ios::binary);

    if (input) {
        // Определяем размер файла, используя метод seekg() и tellg()
        input.seekg(0, std::ios::end);
        int file_size = input.tellg();
        input.seekg(0, std::ios::beg);

        // Выделяем буфер размером, достаточным для хранения содержимого файла
        char* buffer = new char[file_size];

        // Считываем содержимое файла в буфер
        input.read(buffer, file_size);

        // Выводим содержимое буфера на экран
        std::cout.write(buffer, file_size);

        // Освобождаем выделенную память
        delete[] buffer;
    }
    else {
        std::cerr << "Failed to open file." << std::endl;
    }

    return 0;
}
