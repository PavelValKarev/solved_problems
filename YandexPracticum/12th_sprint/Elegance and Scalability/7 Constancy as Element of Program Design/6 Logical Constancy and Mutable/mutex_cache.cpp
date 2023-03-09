#include <iostream>
#include <string>
#include <unordered_map>
#include <mutex>

using namespace std;

/*
Другой пример подобного поля, которое не относится к логической константности,
но является частью реализации, — мьютекс, обеспечивающий синхронизацию потоков
при обращении к объекту.
 
Допустим, с объектом класса PasswordCracker работает несколько потоков.
В этом случае даже используя константность объекта, мы рискуем оказаться
в состоянии гонки, когда два потока одновременно будут записывать подобранный
пароль в cached_passwords_. Нужно защитить этот внутренний объект мьютексом.
Так как мьютекс будет менять своё состояние, его нужно сделать mutable и
немного переписать метод BruteForce:
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
        auto result = caсhed_passwords_.find(curr_check_key_);
        if (caсhed_passwords_.end() != result) {
            return result->second;
        }        
        auto pass = BruteForceInternal(""s, 0);
        //захватим мьютекс, чтобы избежать ситуации гонки
        lock_guard lock(cache_quard_);
        /*
        Теперь поля, относящиеся к наблюдаемому состоянию, надёжно
        защищены константностью, а поля, относящиеся к реализации,
        объявлены mutable, что дало возможность ускорить поиск из
        подобранных паролей и при этом защитить кэш от состояния
        гонки.
        */
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
    mutable unordered_map<string, string> caсhed_passwords_;
    mutable mutex cache_quard_;
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
