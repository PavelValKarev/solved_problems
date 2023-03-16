#include <iostream>
#include <ranges>

namespace rng = std::ranges;
namespace view = rng::views;

using namespace std;

int main() {

    setlocale(LC_ALL, "Ru");

    const int days = 3;   // количество дней с играми
    const int games = 2;  // количество игр с питомцем в день

    // раньше:
    for (int i = 0; i < days; i++) {
        cout << "День "sv << i << endl;
        for (int j = 0; j < games; j++) {
            cout << "  Игра "sv << j << endl;
        }
    }

    // сейчас:
    for (int i : view::iota(0, days)) {
        cout << "День "sv << i << endl;
        for (int j : view::iota(0, games)) {
            cout << "  Игра "sv << j << endl;
        }
    }
}
