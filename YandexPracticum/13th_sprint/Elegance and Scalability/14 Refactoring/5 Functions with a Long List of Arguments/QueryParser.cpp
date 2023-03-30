/*
Превращение функции в метод класса
Если требуется распарсить поток запросов с одинаковыми настройками,
стоит рассмотреть вариант создания класса QueryParser с 
инициализацией по одной из рассмотренных выше методологий
и методом Parse:
*/

class QueryParser {
public:
    QueryParser(const ParsingParams& params);
    Query Parse(string_view text, int country_id);
};

// ...

QueryParser parser(ParsingParams{ .max_word_count = 7,
                                 .max_word_length = 23,
                                 .max_form_count_per_word = 20,
                                 .allow_minus_words = true,
                                 .keep_stop_words = false,
                                 .case_sensitive = false });

// ...

const Query query = parser.Parse(text, 225);
