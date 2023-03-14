#include <iostream>
#include <optional>
#include <string>

std::optional<int> get_int(bool some_condition) {
    if (some_condition) {
        return 42;
    }
    else {
        return std::nullopt;
    }
}

int main() {
    std::optional<int> my_int = get_int(true);
    if (my_int.has_value()) {
        std::cout << "Value is: " << my_int.value() << std::endl;
    }
    else {
        std::cout << "Value is not set" << std::endl;
    }

    std::optional<std::string> my_string = "hello";
    if (my_string.has_value()) {
        std::cout << "String is: " << *my_string << std::endl;
    }
    else {
        std::cout << "String is not set" << std::endl;
    }

    return 0;
}
