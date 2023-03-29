/*
Сформулируем точнее проблему, которая возникла в конце прошлого урока. 
У объекта ReadingManager есть две фазы жизненного цикла: инициализация
и использование. Использование невозможно до окончания инициализации. 
Нужно разделить эти две фазы, чтобы гарантировать их непересечение.
Проблема сформулирована, решим её. Выделим отдельный класс для
инициализации и назовём его ReadingManagerBuilder:
*/

class ReadingManagerBuilder {
public:
    void SetMaxUserCount(int max_user_count) {
        max_user_count_ = max_user_count;
    }

    void SetMaxPageCount(int max_page_count) {
        max_page_count_ = max_page_count;
    }

    void SetCheerFactor(double cheer_factor) {
        cheer_factor_ = cheer_factor;
    }

    ReadingManager Build() const {
        if (max_user_count_ <= 0) {
            // ...
        }
        return { max_user_count_, max_page_count_, cheer_factor_ };
    }

private:
    int max_user_count_;
    int max_page_count_;
    double cheer_factor_;
};

/*
Теперь можно вернуть на место конструктор ReadingManager с тремя параметрами. 
Однако сделать это нужно хитро. Программист бы не хотел, чтобы обычный
пользователь вызывал этот конструктор. Но у ReadingManagerBuilder должно получиться.

Ключевое слово friend разрешит методам класса ReadingManagerBuilder доступ
к секции privateкласса  ReadingManager.
Выглядеть это будет так:
*/

class ReadingManager {
public:
    friend class ReadingManagerBuilder;
    ...

private:
    vector<int> user_page_counts_;
    vector<int> page_achieved_by_count_;
    double cheer_factor_ = 0;

    ReadingManager(int max_user_count, int max_page_count, double cheer_factor)
        : user_page_counts_(max_user_count + 1, -1),
        page_achieved_by_count_(max_page_count + 1, 0),
        cheer_factor_(cheer_factor)
    {
    }

    ...
};

//Теперь пользователь надёжно защищён от недоразумений:

ReadingManagerBuilder builder;
builder.SetMaxUserCount(20000);
builder.SetMaxPageCount(1000);
builder.SetCheerFactor(2);
ReadingManager manager = builder.Build();
