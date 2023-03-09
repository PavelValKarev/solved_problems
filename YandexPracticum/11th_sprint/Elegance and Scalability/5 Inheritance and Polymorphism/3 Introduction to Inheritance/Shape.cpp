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
