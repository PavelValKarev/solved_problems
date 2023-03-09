class Document {
public:
    // output используется только для записи документа
    void SaveToStream(ostream& output) const {
        output << title_ << endl;
        output << text_ << endl;
    }
    // input используется только для чтения документа
    void LoadFromStream(istream& input) {
        getline(input, title_);
        text_.clear();
        string line;
        while (getline(input, line)) {
            if (!text_.empty()) {
                text_ += '\n'; // Добавляем символ перевода строки перед каждой строкой, кроме первой
            }
            text_ += line;
        }
    }
private:
    string title_;
    string text_;
};
