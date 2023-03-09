struct Point {
    double x = 0;
    double y = 0;
};

enum class Color { BLACK, RED, GREEN, BLUE };

class Shape {
public:
    explicit Shape(Color color)
        : color_(color) {
    }

    Color GetColor() const {
        return color_;
    }

private:
    Color color_;
};

class Circle : public Shape {
public:
    Circle(Color color, Point center, double radius)
        : Shape(color)  // Передаём цвет конструктору родительского класса
        , center_(center)
        , radius_(radius) {
    }

    Point GetCenter() const {
        return center_;
    }
    void SetCenter(Point center) {
        center_ = center;
    }

    double GetRadius() const {
        return radius_;
    }
    void SetRadius(double radius) {
        radius_ = radius;
    }

private:
    Point center_;
    double radius_;
};

/*
Унаследованный от Shape класс Circle должен явно вызвать 
параметризованный конструктор родителя, передав ему нужное значение цвета:
*/
int main() {
    // Красная окружность с центром в точке {1, 2} радиусом 5
    Circle c{ Color::RED, {1, 2}, 5 };
}
