// Книга - пример композиции экземпляров string и int.
class Book {
    ...
private:
    string title_;
    string author_;
    string isbn_; // ISBN - уникальный номер книжного издания
    int publication_year_; // Год публикации
};

// Человек - ещё один пример композиции экземпляров string и int
class Person {
private:
    string name_;
    string address_;
    int birth_year_;
};
