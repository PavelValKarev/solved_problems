#include <iostream>
#include <ranges>

int main() {
    auto numbers = std::views::iota(1, 11); // создание последовательности от 1 до 10

    // вывод элементов последовательности
    for (auto number : numbers) {
        std::cout << number << ' ';
    }

    return 0;
}
