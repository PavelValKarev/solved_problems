/*
Например, нет особого смысла создавать в программе экземпляры
класса Shape, ведь этот класс — слишком абстрактная сущность.
Объявив конструктор Shape защищённым, сможете создавать в
программе только экземпляры конкретных фигур, таких как 
окружности и прямоугольники:
*/

class Shape {
public:
    ...
protected:
    // Этот конструктор доступен только классам-наследникам
    explicit Shape(Color color)
        : color_(color) {
    }
private:
    Color color_;
    ...
};

class Circle : public Shape {
public:
    Circle(double radius, Color color)
        : Shape(color)
        , radius_(radius) {
    }
    ...
private:
    double radius_;
    ...
};

int main() {
    Shape shape(Color::RED); // Ошибка компиляции - конструктор Shape недоступен
    Circle circle(10.0, Color::RED); // OK - экземпляр Circle имеет публичный конструктор
}
