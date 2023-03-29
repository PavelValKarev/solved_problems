//использование методов-сеттеров, чтобы сделать
//конструирование объектов более понятным

class ReadingManager {
public:
    ReadingManager();

    void SetMaxUserCount(int max_user_count) {
        max_user_count_ = max_user_count;
    }

    void SetMaxPageCount(int max_page_count) {
        max_page_count_ = max_page_count;
    }

    void SetCheerFactor(double cheer_factor) {
        cheer_factor_ = cheer_factor;
    }
    ...
private:
    int max_user_count_ = 0;
    int max_page_count_ = 0;
    double cheer_factor_ = 0;
};

//Теперь подготовка объекта класса ReadingManager будет выглядеть так:

ReadingManager manager;
manager.SetMaxUserCount(20000);
manager.SetMaxPageCount(1000);
manager.SetCheerFactor(2);

//Пока всё в порядке, но вдруг кто-нибудь из пользователей решил вызвать
//другие методы класса ReadingManager до вызова сеттеров:

ReadingManager manager;
manager.Read(0, 1);

/*Пользователь прав. Ничего не мешает ему сделать именно так. 
Но это добавляет нам проблем.
Теперь после вызова конструктора объект на самом деле не сконструирован
до конца, использование его методов вызывает неопределённое поведение.
Такой способ рефакторинга может работать, но, как видите, он тоже не 
идеален. Продолжим улучшать код в следующем уроке.*/



