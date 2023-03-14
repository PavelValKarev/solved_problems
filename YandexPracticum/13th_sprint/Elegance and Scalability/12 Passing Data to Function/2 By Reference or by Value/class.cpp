struct User {
    int user_id_;
    int score_;
};

// Принимаем User по ссылке, несмотря на то, что он хранит только
// два значения int. В дальшейшем, скорее всего, расширим его.
void PrintUserInfo(const User& user);
