template<typename T>
concept Iterable = requires(T t) {
    t.begin();
    t.end();
};

template<Iterable T>
void myFunction(T container) {
    // ...
}
