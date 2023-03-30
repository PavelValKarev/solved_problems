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
