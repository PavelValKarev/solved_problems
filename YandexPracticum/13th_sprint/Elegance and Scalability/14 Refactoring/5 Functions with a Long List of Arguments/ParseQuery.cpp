//гипотетическая функция парсинга строки
//с большим кол-вом аргументов

Query ParseQuery(string_view text,
    int country_id,
    int max_word_count,
    int max_word_length,
    int max_form_count_per_word,
    bool allow_minus_words,
    bool keep_stop_words,
    bool case_sensitive);

//вызов функции может доставить дискомфорт
const Query query = ParseQuery(text, 225, 7, 23, 20, true, false, false);

//Аргументы можно снабжать комментариями, но это не защитит от ошибок:
const Query query = ParseQuery(text, /* country_id */ 7,
    /* max_word_count */ 225,
    /* max_word_length */ 23,
    /* max_form_count_per_word */ 20,
    /* allow_minus_words */ true,
    /* keep_stop_words */ false,
    /* case_sensitive */ false);
