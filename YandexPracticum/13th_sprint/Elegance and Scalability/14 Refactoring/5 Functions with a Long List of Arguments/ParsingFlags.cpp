/*
Довольно неудобно писать всюду static_cast, поэтому можно создать
простой шаблон Flags и определить для Flags<ParsingFlag> и 
ParsingFlag операторы & и | так, чтобы следующий код работал, 
как предыдущий:
*/

enum class ParsingFlag {
    ALLOW_MINUS_WORDS = 1 << 0,
    KEEP_STOP_WORDS = 1 << 1,
    CASE_SENSITIVE = 1 << 2
};

using ParsingFlags = Flags<ParsingFlag>;

Query ParseQuery(string_view text, int country_id, int max_word_count, int max_word_length, int max_form_count_per_word,
    ParsingFlags flags) {
    // ...
    if (flags & ParsingFlag::KEEP_STOP_WORDS) {
        // обработка запроса с учётом флага KEEP_STOP_WORDS
    }
    // ...
}

// ...

const Query query = ParseQuery(text, 225, 7, 23, 20,
    ParsingFlag::ALLOW_MINUS_WORDS | ParsingFlag::KEEP_STOP_WORDS);
