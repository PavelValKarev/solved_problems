/*
Структура для параметров

В случае функции ParseQuery можно было бы
вынести в ParsingParams последние шесть параметров:
*/

const Query query = ParseQuery(text, 225,
    ParsingParams().
    SetMaxWordCount(7).
    SetMaxWordLength(23).
    SetMaxFormCountPerWord(20).
    SetAllowMinusWords(true));

/*
Параметрам keep_stop_words и case_sensitive можно 
присвоить значения по умолчанию, которые они получат
при отсутствии вызова соответствующих Set-методов. 
Это позволит не указывать их при инициализации ParsingParams.

Вот так будет выглядеть вызов функции при использовании
designated initializers. Зададим все параметры для наглядности:
*/

const Query query = ParseQuery(text, 225,
    { .max_word_count = 7,
     .max_word_length = 23,
     .max_form_count_per_word = 20,
     .allow_minus_words = true,
     .keep_stop_words = false,
     .case_sensitive = false });
