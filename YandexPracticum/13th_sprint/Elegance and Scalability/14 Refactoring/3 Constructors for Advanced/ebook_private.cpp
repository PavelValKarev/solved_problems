#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class ReadingManager {
public:    

    //сделаем friend для обращения к приватному полю
    //с конструктором с тремя параметрами
    friend class ReadingManagerBuilder;

    void Read(int user_id, int page_count) {
        UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
        user_page_counts_[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        const int pages_count = user_page_counts_[user_id];
        if (pages_count == -1) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Один из простых способов сделать это — умножить его на 1.0.
        return (user_count - page_achieved_by_count_[pages_count]) * 1.0 / (user_count - 1);
    }

private:

    int max_user_counts_{};

    // Номер страницы, до которой дочитал пользователь <ключ>
    vector<int> user_page_counts_;
    // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
    vector<int> page_achieved_by_count_;
    double cheer_factor_{};

    //перенесем коснтруктор в приватную область
    //чтобы не дать возможность его вызывать снаружи
    ReadingManager(int max_user_count, int max_page_count, double cheer_factor)
        : user_page_counts_(max_user_count + 1, -1),
        page_achieved_by_count_(max_page_count + 1, 0),
        cheer_factor_(cheer_factor)
    {
    }

    int GetUserCount() const {
        return page_achieved_by_count_[0];
    }

    void UpdatePageRange(int lhs, int rhs) {
        for (int i = lhs; i < rhs; ++i) {
            ++page_achieved_by_count_[i];
        }
    }
};

class ReadingManagerBuilder {
public:

    
    //методы просто заполняют поля
    void SetMaxUserCount(int max_user_count) {
        max_user_count_ = max_user_count;
    }

    void SetMaxPageCount(int max_page_count) {
        max_page_count_ = max_page_count;
    }

    void SetCheerFactor(double cheer_factor) {
        cheer_factor_ = cheer_factor;
    }

    //метод Build() принимает ничего и является константным 
    ReadingManager Build() const;

private:
    int max_user_count_{};
    int max_page_count_{};
    double cheer_factor_{};

};

int main() {
    ReadingManagerBuilder builder;
    builder.SetMaxUserCount(100000);
    builder.SetMaxPageCount(1000);
    builder.SetCheerFactor(2); 

    //создадим новый ReadingManager с помощью 
    //метода Build() у buider-а
    ReadingManager manager = builder.Build();

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; query_id++) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ"s) {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER"s) {
            cout << setprecision(6) << manager.Cheer(user_id) << endl;
        }
    }
}

//метод Build() принимает ничего и является константным 

inline ReadingManager ReadingManagerBuilder::Build() const {
    //проверки на инициализацию можно перенести 
    //сюда в метод Build() и если что-то не так
    //то кинуть исключения
    if (max_user_count_ <= 0) {
        throw domain_error("max_user_count_ <= 0");
    }
    //в этом методе мы создадим объект ReadingManager
    //передав в его конструктор параметры
    return { max_user_count_, max_page_count_, cheer_factor_ };

}
