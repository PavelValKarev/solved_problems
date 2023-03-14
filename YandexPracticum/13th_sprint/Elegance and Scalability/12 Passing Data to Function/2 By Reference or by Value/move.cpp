class SearchServer {
public:
    // принимаем вектор по значению - функция принимает владение объектом
    void SetStopWords(std::vector<std::string> stop_words) {
        stop_words_ = std::move(stop_words);
    }

private:
    std::vector<std::string> stop_words_;
};
