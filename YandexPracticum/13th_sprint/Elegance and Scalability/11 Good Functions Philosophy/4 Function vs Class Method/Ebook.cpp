#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



class ReadersDataBase {
public:
    void Read(int user, int page) {

        if (user >= readers.size()) {
            readers.resize(user + 1);
        }

        if (readers[user] > 0) {

            //reader читает от страницы на которой остановился ранее
            //и до вновь заданной страницы, а не перечитывает книгу
            //повтроно с первой страницы
            for (size_t m = readers[user] + 1; m <= page; ++m) {

                ebook[m]++;
            }

        }

        else {

            //общее число читателей
            ++readers_count;

            for (size_t m = 0; m <= page; ++m) {
                ebook[m]++;
            }

        }

        readers[user] = page;

    }

    double Cheer(int user) {

        if (user >= readers.size()) {
            readers.resize(user + 1);
        }

        int pages_read_by_user = readers[user];

        if ((readers_count == 1) && (readers[user] > 0)) {
            return 1;
        }

        else if (ebook[pages_read_by_user] == 0) {
            return 0;
        }

        else {

            int readers_on_page = ebook[pages_read_by_user];

            int less_readers = readers_count - readers_on_page;
            if (less_readers == 0) {
                return 0;
            }

            else {
                double stats{};
                stats = (static_cast<double>(less_readers) / (readers_count - 1));
                return stats;
            }

        }

    }

private:
    vector<int> readers = vector<int> {};
    vector<int> ebook = vector<int>(1001, 0);
    int readers_count = 0;
};

void ProcessRequests(istream& in, ostream& out) {
    string command{};
    ReadersDataBase db{};
    string line;
    if (in) {
        size_t num_of_requests{};
        in >> num_of_requests;
        for (size_t i = 0; i < num_of_requests; i++) {

            in >> command;
            if (*command.begin() == 'R') {
                int user{}, page{};
                in >> user >> page;
                db.Read(user, page);
            }
            else if (*command.begin() == 'C') {
                int user;
                in >> user;
                out << db.Cheer(user) << endl;
            }
        }
    }
}

int main() {

    ifstream in_file("input.txt"s);
    //ProcessRequests(in_file, cout);
    ProcessRequests(cin, cout);
}
