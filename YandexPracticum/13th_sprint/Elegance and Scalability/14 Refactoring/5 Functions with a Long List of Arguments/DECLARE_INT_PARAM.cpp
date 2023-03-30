/*
Отдельные типы для числовых параметров
Наконец, посмотрим, что сделать с числовыми параметрами функций
для повышения прозрачности и безопасности вызовов.
Безопасности не будет без типизации. Поэтому определим для 
каждого числового параметра свой тип с explicit-конструктором:
*/

struct CountryId {
    int value;
    explicit CountryId(int v)
        : value(v)
    {
    }
};

struct MaxWordCount {
    int value;
    explicit MaxWordCount(int v)
        : value(v)
    {
    }
};

struct MaxWordLength {
    int value;
    explicit MaxWordLength(int v)
        : value(v)
    {
    }
};

struct MaxFormCountPerWord {
    int value;
    explicit MaxFormCountPerWord(int v)
        : value(v)
    {
    }
};

Query ParseQuery(string_view text,
    CountryId country_id,
    MaxWordCount max_word_count,
    MaxWordLength max_word_length,
    MaxFormCountPerWord max_form_count_per_word,
    bool allow_minus_words,
    bool keep_stop_words,
    bool case_sensitive);

// ...

const Query query = ParseQuery(text, CountryId(225),
    MaxWordCount(7),
    MaxWordLength(23),
    MaxFormCountPerWord(20),
    true, false, false);

/*
То же можно проделать и для булевых параметров.
Определение каждой такой структуры довольно однотипно,
поэтому напрашивается макрос DECLARE_INT_PARAM:
*/

#define DECLARE_INT_PARAM(Name) \
    struct Name {               \
        int value;              \
        explicit Name(int v)    \
            : value(v) {        \
        }                       \
    }

DECLARE_INT_PARAM(CountryId);
DECLARE_INT_PARAM(MaxWordCount);
DECLARE_INT_PARAM(MaxWordLength);
DECLARE_INT_PARAM(MaxFormCountPerWord);

/*
Можно доработать этот макрос так, чтобы разрешить подобным
типам автоматически приводиться к int. Вы избавите авторов
функции от необходимости постоянно обращаться к полю value:
*/

#define DECLARE_INT_PARAM(Name) \
    struct Name {               \
        int value;              \
        explicit Name(int v)    \
            : value(v) {        \
        }                       \
        operator int() const {  \
            return value;       \
        }                       \
    }

/*
Ещё один способ создания подобных типов, принятый в том числе
и в стандартной библиотеке, — определение специальных суффиксов.
Они позволяют писать так:
*/

const Query query = ParseQuery(text, CountryId(225),
    7_words, 23_letters, 20_forms,
    true, false, false);

/*
Определение таких суффиксов возможно благодаря строковым литералам,
о которых уже шла речь в спринте 11. operator"" решает эту задачу так:
*/

auto operator""_words(unsigned long long value) {
    return MaxWordCount(value);
}

auto operator""_letters(unsigned long long value) {
    return MaxWordLength(value);
}

auto operator""_forms(unsigned long long value) {
    return MaxFormCountPerWord(value);
}

/*
Числовой параметр такого оператора обязан иметь тип unsigned long long.
По сути выражение 7_words эквивалентно вызову operator""_words(7) и, 
в конечном счёте, MaxWordCount(7).
*/
