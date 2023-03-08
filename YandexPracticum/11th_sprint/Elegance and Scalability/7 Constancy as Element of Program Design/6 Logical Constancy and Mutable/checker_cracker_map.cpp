#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
Но предположим, возникла необходимость улучшить класс PasswordCracker. 
Алгоритм подбора пароля занимает слишком много времени, и даже если функция
проверки check одинаковая, каждый раз поиск будет запущен с нуля. Можно
добавить в класс PasswordCracker простой механизм кэширования.
*/

/*
Пусть вместе с проверяющей функцией пользователь передаёт ключ-строку.
Внутри класса PasswordCracker будет храниться словарь, содержащий связки
«ключ — найденный пароль». Теперь поиск пароля, который уже найден,
будет выполнен за логарифмическое время:
*/

template <typename Checker>
class PasswordCracker {
public:
    PasswordCracker(Checker check, string key)
        : check_(check)
        , curr_check_key_(move(key))
        , caсhed_passwords_()
    {
    }
    //меняет значение поля
    void SetCheck(Checker check, string key) {
        check_ = check;
        curr_check_key_ = move(key);
    }
    string BruteForce() const {
        //если готовый пароль есть в словаре, вернем его
        auto result = caсhed_passwords_.find(curr_check_key_);
        if (caсhed_passwords_.end() != result) {
            return result->second;
        }
        //если готового пароля нет, то перейдем к повтору
        auto pass = BruteForceInternal(""s, 0);
        //не забудем добавить новый пароль в словарь готовых паролей
        caсhed_passwords_[move(curr_check_key_)] = pass;
        return pass;
    }

private:
    string BruteForceInternal(const string& begin, int n) const {
        if (n == 5) {
            return check_(begin) ? begin : ""s;
        }

        for (char c = 'A'; c != 'Z' + 1; ++c) {
            string res = BruteForceInternal(begin + string({ c }), n + 1);
            if (!res.empty()) {
                return res;
            }
        }

        return {};
    }
    Checker check_;
    string curr_check_key_;

    //словарь для кэширования найденных паролей

    /*
    Логическая константность не пострадает, если словарь будет изменён.
    Кэш паролей — не часть наблюдаемого состояния объекта. Для полей, 
    подобных кэш-словарю, есть ключевое слово mutable. Оно позволяет
    изменять это поле у константных объектов:
    */
    mutable unordered_map<string, string> caсhed_passwords_;
};

class PasswordChecker {
public:
    PasswordChecker(string match)
        : match_(match)
    {
    }
    bool operator()(const string& s) const {
        return s == match_;
    }
    void operator=(const PasswordChecker& other) {
        match_ = other.match_;
    }

private:
    string match_;
};

string GetShmandexPass(const PasswordCracker<PasswordChecker>& pass_cracker) {
    // если раскомментировать код ниже, программа не скомпилируется
    // PasswordChecker.check("BUY"s);
    // pass_cracker.SetCheck(check);
    return pass_cracker.BruteForce();
}

int main() {
    PasswordChecker check("HELLO"s);

    string key{};

    PasswordCracker password_cracker(check, key);
    cout << GetShmandexPass(password_cracker) << endl;
    cout << GetShmandexPass(password_cracker) << endl;
}
