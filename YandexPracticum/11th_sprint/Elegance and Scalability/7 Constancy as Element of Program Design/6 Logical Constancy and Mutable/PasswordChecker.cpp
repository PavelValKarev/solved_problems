#include <iostream>
#include <string>

using namespace std;

template <typename Checker>
class PasswordCracker {
public:
    PasswordCracker(Checker check)
        : check_(check)
    {
    }
    //меняет значение поля
    void SetCheck(Checker check) {
        check_ = check;
    }
    string BruteForce() const {
        return BruteForceInternal(""s, 0);
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
    PasswordCracker password_cracker(check);
    cout << GetShmandexPass(password_cracker) << endl;
}
