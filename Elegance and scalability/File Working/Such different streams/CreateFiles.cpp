#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

using namespace std;

string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

// реализуйте эту функцию:
void CreateFiles(const string& config_file) {
    //в конструктор input подается имя файла из которого читаем
    ifstream in_file(config_file);
    //сюда будем класть считанные строки
    string line; 
    //сюда будем писать путь к файлу через директории '\'
    string path{};
    //проверка на то что файл открыт
    if (in_file.is_open()) {
    
        // пока не достигнут конец файла класть очередную строку в переменную (line)
        while (getline(in_file, line)) {
        //---------------------------------------------------------------------------------
        //Здесь решается проблема с сосзданием пути папка\папка...\файл    
            //создаем выходной поток
            path = line;
            string directory;
            for (int i = 0; i < path.length(); i++) {
                if (path[i] == '/' || path[i] == '\\') {
                    /*int err = */system(("mkdir "s + directory + " 2>nul").c_str());
                    directory.push_back('\\');
                }
                else {
                    directory.push_back(path[i]);
                }
            }
        //----------------------------------------------------------------------------------
            ofstream out_file(line);
            //пока первый символ в getline '>'
            while (in_file.peek() == '>') {
                char delim{};
                //записываем посимвольно во входной поток
                in_file >> delim;
                //считываем записанную строку из in_file в line
                getline(in_file, line);
                out_file << line << endl;
            }            
        }
    }

    else {
        //если файл не открыт
        cout << "error!" << endl;
    }
}

int main() {
    ofstream("test_config.txt"s) << "a.txt\n"
        ">10\n"
        ">abc\n"
        "b.txt\n"
        ">123"sv;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);

    ofstream("test_config.txt"s) << "shakespeare/hamlet.txt\n"
        ">To be, or not to be,\n"
        ">that is the question;\n"
        "empty.txt\n"
        "shakespeare/lear.txt\n"
        ">Nor are those empty-hearted whose low sound\n"
        ">Reverbs no hollowness."sv;

    CreateFiles("test_config.txt"s);
}
