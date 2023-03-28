/*
Функция с побочными эффектами в идеале вообще не имеет
return. Пример такой функции — сеттер класса:
*/

class Person {
public:
    void SetCat(Cat cat) {
        my_cat_ = std::move(cat);
    }

private:
    Cat my_cat_;
};
