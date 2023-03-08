#pragma once
#include "common.h"

class Texture {
public:
    explicit Texture(Image image)
        /*: image_(std::move(image))*/ {
        //Реализуйте метод самостоятельно
        if (image.size() > 0)
            image_ = std::move(image);
    }

    Size GetSize() const {
        //Реализуйте метод самостоятельно
        return GetImageSize(image_);
    }

    char GetPixelColor(Point p) const {
        if (p.x >= (signed int)image_[0].size() || p.y >= (signed int)image_.size())
            return '.';
        return image_[p.y][p.x];
    }

private:
    Image image_;
};
