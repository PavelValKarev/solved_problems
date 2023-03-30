/*
Объединение булевых параметров в маску
Беззнаковые числовые типы часто используются как хранилище битов:
например, число типа uint64_t позволяет сохранить 64 булевых значения.
Поэтому булевы флаги можно объединить в один enum ParsingFlag и
собрать из подручных средств такую конструкцию:
*/

enum class ParsingFlag {
    // значения, являющиеся степенями двойки,
    // позволяют работать с масками без дополнительных
    // преобразований вида 1 << value
    ALLOW_MINUS_WORDS = 1 << 0,  // 001
    KEEP_STOP_WORDS = 1 << 1,    // 010
    CASE_SENSITIVE = 1 << 2      // 100
};

using ParsingFlags = uint64_t;

Query ParseQuery(string_view text, int country_id, int max_word_count, int max_word_length, int max_form_count_per_word,
    ParsingFlags flags) {
    // ...
    if (flags & static_cast<ParsingFlags>(ParsingFlag::KEEP_STOP_WORDS)) {
        // обработка запроса с учётом флага KEEP_STOP_WORDS
    }
    // ...
}

// ...

const Query query = ParseQuery(text, 225, 7, 23, 20,
    static_cast<ParsingFlags>(ParsingFlag::ALLOW_MINUS_WORDS)
    | static_cast<ParsingFlags>(ParsingFlag::KEEP_STOP_WORDS));
// выключенные флаги не указываются в списке
