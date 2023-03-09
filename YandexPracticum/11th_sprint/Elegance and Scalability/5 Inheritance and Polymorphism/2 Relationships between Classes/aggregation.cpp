template <typename T>
class SingleLinkedList {
    struct Node {
        ...
        T value{};
        Node* node_ = nullptr;
    };
public:
    class Iterator {
        ...
    private:
        // Итератор хранит адрес узла списка, но не владеет им
        Node* node_;
    };
};
