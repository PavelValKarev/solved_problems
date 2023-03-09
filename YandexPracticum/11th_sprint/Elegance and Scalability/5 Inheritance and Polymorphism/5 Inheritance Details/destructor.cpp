/*
Деструкторы и наследование
В C++ для удаления объектов, которые созданы в динамической памяти с
использованием оператора new, служит оператор delete. 
Помимо освобождения памяти, занимаемой объектом, он предварительно
выполняет вызов деструктора удаляемого объекта:
*/

/*
Circle* circle = new Circle(Color::RED);
delete circle;
*/


/*
При публичном наследовании указатели и ссылки на дочерние классы 
могут приводиться к указателям и ссылкам на класс-родитель. Это 
даёт возможность единообразно взаимодействовать с подклассами, 
используя ссылку или указатель на их общего родителя:

*/

// Функция DoSomething может обработать вектор указателей на любые фигуры
/*
void DoSomething(const vector<Shape*>& shapes);
*/

using namespace std;

int main() {
    Circle* circle = new Circle(10, Color::RED);
    Rectangle* rectangle = new Rectangle(10, 20, Color::BLUE);
    vector<Shape*> shapes = { &circle, &rectangle };

    DoSomething(shapes);

    Shape* shape = new Circle(10, Color::RED);
    delete shape; // Что произойдёт?

    return 0;
}

/*
Когда оператор delete удаляет экземпляр класса-наследника
через указатель на родительский класс, деструктор родителя
должен быть виртуальным. Иначе оператор delete вызовет
неопределённое поведение:
*/

class Shape {
public:
    ...
        // Помечаем деструктор виртуальным. Компилятор сам сгенерирует тело деструктора
        virtual ~Shape() = default;
    /*
    virtual ~Shape() {
        // Также можно написать тело деструктора вручную
    }
    */
    ...
};

class Circle : public Shape { ... };

int main() {
    Shape* shape = new Circle(10, Color::RED);
    delete shape; // OK, так как деструктор Shape виртуальный
}

/*
Практически всегда сто́ит объявлять деструктор базового класса
публичным и виртуальным. Так вы избежите проблем при удалении
его наследников через указатель на базовый класс. Например
когда в контейнере хранятся умные указатели на базовый класс
иерархии:
*/

class Shape {
public:
    virtual ~Shape() = default;
    ...
};

class Circle : public Shape { ... };
class Rectangle : public Shape { ... };

int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.emplace_back(make_unique<Circle>(10.0, Color::RED));
    shapes.emplace_back(make_unique<Rectangle>(10.0, 20.0, Color::BLUE));
    // Деструкторы unique_ptr корректно удалят фигуры через указатель на класс Shape
}
