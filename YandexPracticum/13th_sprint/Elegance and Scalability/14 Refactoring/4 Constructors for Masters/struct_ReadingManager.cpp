/*
Подход 2. Принимать в конструкторе ReadingManager структуру,
созданную с помощью Set-методов
Если у конструктора ReadingManager слишком много параметров,
объединим эти параметры в структуру.
*/

class ReadingManager {
public:
    ReadingManager(const ReadingManagerParams& params);
    // ...

private:
    // ...
};

/*
Структуру ReadingManagerParams можно почти полностью
списать с ReadingManagerBuilder:
*/

struct ReadingManagerParams {
    int max_user_count;
    int max_page_count;
    double cheer_factor;

    ReadingManagerParams& SetMaxUserCount(int max_user_count) {
        this->max_user_count = max_user_count;
        return *this;
    }

    ReadingManagerParams& SetMaxPageCount(int max_page_count) {
        this->max_page_count = max_page_count;
        return *this;
    }

    ReadingManagerParams& SetCheerFactor(double cheer_factor) {
        this->cheer_factor = cheer_factor;
        return *this;
    }
};

//Создание ReadingManager будет выглядеть следующим образом:

ReadingManager manager(
    ReadingManagerParams().
    SetMaxUserCount(10000).
    SetMaxPageCount(500).
    SetCheerFactor(2)
);
