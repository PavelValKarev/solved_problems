#include <iostream>
#include <span>

template <typename T>
void print_span(std::span<T> s) {
  std::cout << "Size of span: " << s.size() << std::endl;
  for (const auto& elem : s) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  std::span<int> s(arr, 5);

  print_span(s); // вызов функции

  return 0;
}
