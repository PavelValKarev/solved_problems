#include <string>
#include <fstream>
#include <iostream>
#include <string_view>

using namespace std;

int main(int argc, const char** argv) {

    ofstream("argv"s) <<
                "3 clap\n"
                "3 jump\n"
                "turn\n"
                "3 stomp"sv;

    // открываем файл, указанный в первом аргументе командной строки
    ifstream input/*(argv[1])*/;
    input.open("argv");

    while (input) {
        int times;
        string action;

        if (input >> times >> action) {
            for (int i = 0; i < times; ++i) {
                cout << action << "! "sv;
                
            }
            cout << endl;
            
        }
        else {
            string action2;
            // сбрасываем флаги ошибок перед новым чтением:
            input.clear();
            if (input >> action2) {
                cout << action2 << "!"sv << endl;
            }
        }
    }
}
