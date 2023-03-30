/*
Можно избавиться от необходимости вызывать метод Build, 
воспользовавшись оператором приведения типа:
*/

class ReadingManagerBuilder {
public:
    ReadingManagerBuilder& SetMaxUserCount(int max_user_count);
    ReadingManagerBuilder& SetMaxPageCount(int max_page_count);
    ReadingManagerBuilder& SetCheerFactor(double cheer_factor);

    operator ReadingManager() const {
        // throw exception if not valid
        return { max_user_count_, max_page_count_, cheer_factor_ };
    }

private:
    int max_user_count_;
    int max_page_count_;
    double cheer_factor_;
};

/*
Указанный оператор автоматически вызовется при попытке преобразовать
ReadingManagerBuilder к ReadingManager:
*/

ReadingManager manager =
ReadingManagerBuilder().
SetMaxUserCount(10000).
SetMaxPageCount(500).
SetCheerFactor(2);

/*
Код стал более компактным, но непрозрачность такого преобразования
и возможность выброса исключения в процессе него часто становятся
аргументом против этого подхода.
*/
