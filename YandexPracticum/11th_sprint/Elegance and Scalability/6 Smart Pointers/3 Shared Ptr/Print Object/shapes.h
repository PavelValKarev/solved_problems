#pragma once
#include "texture.h"

#include <memory>

// Поддерживаемые виды фигур: прямоугольник и эллипс
enum class ShapeType { RECTANGLE, ELLIPSE };

class Shape {
    Size size_;
    Point position_;
    ShapeType type_;
    std::shared_ptr<Texture> texture_ = nullptr;

public:
    // Фигура после создания имеет нулевые координаты и размер,
    // а также не имеет текстуры
    explicit Shape(ShapeType type) {
        // Заглушка. Реализуйте конструктор самостоятельно
        type_ = type;
    }

    void SetPosition(Point pos) {
        // Заглушка. Реализуйте метод самостоятельно
        position_ = pos;
    }

    void SetSize(Size size) {
        // Заглушка. Реализуйте метод самостоятельно
        size_ = size;
    }

    void SetTexture(std::shared_ptr<Texture> texture) {
        // Заглушка. Реализуйте метод самостоятельно
        if (texture == nullptr)
            return;
        texture_ = std::move(texture);
    }

    // Рисует фигуру на указанном изображении
    // В зависимости от типа фигуры должен рисоваться либо эллипс, либо прямоугольник
    // Пиксели фигуры, выходящие за пределы текстуры, а также в случае, когда текстура не задана,
    // должны отображаться с помощью символа точка '.'
    // Части фигуры, выходящие за границы объекта image, должны отбрасываться.
    void Draw(Image& image) const {
        
        // Реализуйте метод самостоятельно
        if (size_.width == 0 || size_.height == 0)
            return;
        int beginX = std::max(position_.x, 0);
        int endX = std::min(image[0].size(), (size_t)(position_.x + size_.width));

        int beginY = std::max(position_.y, 0);
        int endY = std::min(image.size(), (size_t)(position_.y + size_.height));

        int outsideX = std::max(0, -position_.x);
        int outsideY = std::max(0, - position_.y);

        if (texture_ != nullptr) {
            switch (type_) {
            case ShapeType::RECTANGLE:
                for (int x = beginX; x < endX; x++) {

                    for (int y = beginY; y < endY; y++)
                    {
                        Point localSpaceCoord = { x - beginX + outsideX, y - beginY + outsideY };
                        image[y][x] = texture_.get()->GetPixelColor(localSpaceCoord);
                    }
                }
                   
                break;
            case ShapeType::ELLIPSE:
                for (int x = beginX; x < endX; x++) {

                    for (int y = beginY; y < endY; y++) {
                        Point localSpaceCoord = { x - beginX + outsideX, y - beginY + outsideY };
                        if (IsPointInEllipse(localSpaceCoord, size_))
                            image[y][x] = texture_.get()->GetPixelColor(localSpaceCoord);
                    }
                }

                break;
            default:
                break;
                }
           }
        else {
            for (int x = beginX; x < endX; x++)
                for (int y = beginY; y < endY; y++) {
                    image[y][x] = '.';
                }
        }
        }
        
    
};
