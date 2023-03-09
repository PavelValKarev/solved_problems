struct Point {
    double x = 0;
    double y = 0;
};

enum class Color { BLACK, RED, GREEN, BLUE };

class Shape {
public:
    Color GetColor() const;
    void SetColor(Color color);

private:
    Color color_ = Color::BLACK;
};

class Circle : public Shape {
public:
    Point GetCenter() const;
    void SetCenter(Point center);
    double GetRadius() const;
    void SetRadius(double radius);

private:
    Point center_;
    double radius_ = 1.0;
};
