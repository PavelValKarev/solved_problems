enum class StopWordsMode {
    IGNORE,
    KEEP,
    // в будущем этот класс можно будет расширять
};

Query ParseQuery(string_view text, int country_id, int max_word_count, int max_word_length, int max_form_count_per_word,
    bool allow_minus_words, StopWordsMode stop_words_mode, bool case_sensitive);

// ...

const Query query = ParseQuery(text, 225, 7, 23, 20, true, StopWordsMode::IGNORE, false);
