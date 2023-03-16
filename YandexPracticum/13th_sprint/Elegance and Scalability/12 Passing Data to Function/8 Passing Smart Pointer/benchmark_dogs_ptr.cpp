#include <memory>
#include <string>
#include <string_view>
#include <iostream>

using namespace std;

class Dog {
public:
    explicit Dog(string name)
        : name_(move(name))  //
    {
        cout << name_ << " dog has been created"sv << endl;
    }

    ~Dog() {
        // Все псы попадают в рай
        cout << name_ << " dog has gone to heaven"sv << endl;
    }

private:
    string name_;
};

class Person {
public:
    explicit Person(string name)
        : name_(move(name)) {
    }

    ~Person() {
        cout << name_ << " has died"sv << endl;
    }

    // Стать владельцем собаки
    void OwnDog(shared_ptr<Dog> dog) {
        dog_ = move(dog);
    }

    const shared_ptr<Dog>& GetDog() const {
        return dog_;
    }

    __attribute__((noinline)) bool TestDogVal(shared_ptr<Dog> dog) const {
        return dog_ == dog;
    }

    __attribute__((noinline)) bool TestDogRef(const shared_ptr<Dog>& dog) const {
        return dog_ == dog;
    }

    // Перестаём владеть собакой
    void ReleaseDog() {
        dog_.reset();
        assert(!dog_);  // Указатель обнуляется после вызова reset
    }

private:
    string name_;
    shared_ptr<Dog> dog_;
};

static void TestDogVal(benchmark::State& state) {
    Person ivan("Иван"s);
    auto sharik = make_shared<Dog>("Шарик"s);
    auto barbos = make_shared<Dog>("Барбос"s);

    ivan.OwnDog(sharik);

    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        bool own_sharik = ivan.TestDogVal(sharik);
        bool own_barbos = ivan.TestDogVal(barbos);
        benchmark::DoNotOptimize(own_sharik | own_barbos);
    }
}
// Register the function as a benchmark
BENCHMARK(TestDogVal);

static void TestDogRef(benchmark::State& state) {
    Person ivan("Иван"s);
    auto sharik = make_shared<Dog>("Шарик"s);
    auto barbos = make_shared<Dog>("Барбос"s);

    ivan.OwnDog(sharik);

    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        bool own_sharik = ivan.TestDogRef(sharik);
        bool own_barbos = ivan.TestDogRef(barbos);
        benchmark::DoNotOptimize(own_sharik | own_barbos);
    }
}
// Register the function as a benchmark
BENCHMARK(TestDogRef);
