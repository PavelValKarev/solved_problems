//Возврат пары итераторов

/*
Возвращать пару итераторов можно, только если владение не передаётся.
Иначе получится, что функция отказалась от владения объектами и
возвращённые итераторы указывают в пустоту. Это приведёт к неопределённому поведению.

Возврат пары итераторов более универсален, чем возврат контейнера. Классы могут
определить методы begin и end для последующего использования в for по диапазону.
С таким вы уже сталкивались при написании класса поисковой системы:
*/

class Cohort {
public:
    using StudentMap = std::unordered_map<int, Student>;

    StudentMap::const_iterator begin() const {
        return all_students_.begin();
    }

    StudentMap::const_iterator end() const {
        return all_students_.end();
    }

private:
    StudentMap all_students_;
};

// ...

Cohort cohort100;

// ...

for (const auto& student : cohort100) {
    // ...
}
