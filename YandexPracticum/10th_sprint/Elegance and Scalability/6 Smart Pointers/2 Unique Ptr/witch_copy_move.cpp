#include <iostream>
#include <memory>
#include <string>
#include <cassert>

using namespace std;

struct Cat {
    Cat(const string& name, int age)
        : name_(name)
        , age_(age)  //
    {
        //cout << name_ << " cat was created"s << endl;
    }
    const string& GetName() const noexcept {
        return name_;
    }
    int GetAge() const noexcept {
        return age_;
    }
    ~Cat() {
        //cout << name_ << " cat was destroyed"s << endl;
    }
    void Speak() const {
        cout << "Meow!"s << endl;
    }

private:
    string name_;
    int age_;
};

// Функция создаёт двухлетних котов с заданным именем
unique_ptr<Cat> CreateCat(const string& name) {
    return make_unique<Cat>(name, 2);
}

class Witch {
public:
    Witch(Witch&&) = default;
    Witch& operator=(Witch&&) = default;

    Witch(Witch& old_witch) {
        //копируем имя
        //оно string поэтому просто
        this->name_ = old_witch.name_;
        //для создания нового уникального указателя передаем
        //в make_unique ссылку на оригинального кота в памяти
        //т.е. разименовываем сырой указатель на кота 
        //полученный методом get()
        this->cat_ = make_unique<Cat>(*old_witch.cat_.get());
    }

    Witch& operator=(Witch& old_witch) {
        //создаем копию ведьмы
        Witch witch_copy(old_witch);
        //свапаем поля копии ведьмы, данные которой мы хотим 
        //занести в новую ведьму и поля ведьмы, в которую мы
        //хотим записать данные другой ведьмы
        this->name_.swap(witch_copy.name_);
        this->cat_.swap(witch_copy.cat_);
        return *this;
    }

    explicit Witch(const string& name)
        : name_(name) {
    }

    void SetCat(unique_ptr<Cat>&& cat) noexcept {
        cat_ = std::move(cat);
    }
    unique_ptr<Cat> ReleaseCat() noexcept {
        return std::move(cat_);
    }

private:
    string name_;
    unique_ptr<Cat> cat_;
};

void Test() {
    // Объекты Witch можно перемещать
    {
        //создали объект класса Witch
        Witch witch("Hermione"s);
        //функция возвращает указатель unique_ptr
        auto cat = CreateCat("Crookshanks"s);
        //получаем сырой указатель
        Cat* raw_cat = cat.get();
        //проверяем что в сыром указателе двухлетний кот Croookshanks
        assert(raw_cat);
        //перемещает unique_ptr на кота  внуть witch
        witch.SetCat(move(cat));
        //перемещает указатель от ведьмы witch к ведьме moved_witch  
        //Кот переместился от witch к moved_witch
        Witch moved_witch(std::move(witch));
        auto released_cat = moved_witch.ReleaseCat();
        assert(released_cat.get() == raw_cat);
    }

    // Можно использовать перемещающий оператор присваивания
    {
        Witch witch("Hermione"s);
        auto cat = CreateCat("Crookshanks"s);
        //получили сырой указатель на кота
        Cat* raw_cat = cat.get();
        witch.SetCat(move(cat));

        Witch witch2("Minerva McGonagall");
        //witch2 теперь Гермеона с котом
        witch2 = move(witch);
        //пытаемся возвратить кота
        auto released_cat = witch.ReleaseCat();
        //но его там уже не было, так как он ранее перешел ко второй ведьме
        assert(!released_cat);
        //а здесь кот должен быть
        released_cat = witch2.ReleaseCat();
        //ну и получаем сырой указатель через get()
        assert(released_cat.get() == raw_cat);
    }

    // Можно копировать волшебниц
    {
        Witch witch("Hermione");
        auto cat = CreateCat("Crookshanks"s);
        witch.SetCat(move(cat));

        Witch witch_copy(witch);
        assert(!cat);
        cat = witch.ReleaseCat();
        assert(cat);  // У первой волшебницы кот никуда не делся

        auto cat_copy = witch_copy.ReleaseCat();
        assert(cat_copy != nullptr && cat_copy != cat);
        assert(cat_copy->GetName() == cat->GetName());  // Копия волшебницы содержит копию кота
    }

    // Работает копирующее присваивание волшебниц
    {
        Witch witch("Hermione"s);
        auto cat = CreateCat("Crookshanks"s);
        witch.SetCat(move(cat));

        Witch witch2("Minerva McGonagall"s);
        witch2 = witch;

        assert(!cat);
        cat = witch.ReleaseCat();
        assert(cat);  // У первой волшебницы кот никуда не делся

        auto cat_copy = witch2.ReleaseCat();
        assert(cat_copy != nullptr && cat_copy != cat);
        assert(cat_copy->GetName() == cat->GetName());  // При присваивании скопировался кот
    }
}

int main() {
    Test();
}
