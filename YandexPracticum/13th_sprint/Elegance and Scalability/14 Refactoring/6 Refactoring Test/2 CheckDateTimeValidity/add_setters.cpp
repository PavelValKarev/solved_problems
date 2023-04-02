#include <stdexcept>
#include <array>

using namespace std;

struct DateTime {
    int year{};
    int month{};
    int day{};
    int hour{};
    int minute{};
    int second{};
};

class DateTimeManagerBuilder {
public:
    void SetYear(int year) {
        dt_.year = year;
    }
    void SetMonth(int month) {
        dt_.month = month;
    }
    void SetDay(int day) {
        dt_.day = day;
    }
    void SetHour(int hour) {
        dt_.hour = hour;
    }
    void SetMinute(int minute) {
        dt_.minute = minute;
    }
    void SetSecond(int second) {
        dt_.second = second;
    }

    DateTime Build() const {
        return dt_;
    }

private:
    DateTime dt_;
};

void CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < 1) {
        throw domain_error("year is too small"s);
    }
    if (dt.year > 9999) {
        throw domain_error("year is too big"s);
    }

    if (dt.month < 1) {
        throw domain_error("month is too small"s);
    }
    if (dt.month > 12) {
        throw domain_error("month is too big"s);
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < 1) {
        throw domain_error("day is too small"s);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        throw domain_error("day is too big"s);
    }

    if (dt.hour < 0) {
        throw domain_error("hour is too small"s);
    }
    if (dt.hour > 23) {
        throw domain_error("hour is too big"s);
    }

    if (dt.minute < 0) {
        throw domain_error("minute is too small"s);
    }
    if (dt.minute > 59) {
        throw domain_error("minute is too big"s);
    }

    if (dt.second < 0) {
        throw domain_error("second is too small");
    }
    if (dt.second > 59) {
        throw domain_error("second is too big"s);
    }
}

int main() {

    DateTimeManagerBuilder builder;

    builder.SetYear(2023);
    builder.SetMonth(4);
    builder.SetDay(2);
    builder.SetHour(23);
    builder.SetMinute(45);
    builder.SetSecond(30);   
        
    CheckDateTimeValidity(builder.Build());

    return 0;
}
