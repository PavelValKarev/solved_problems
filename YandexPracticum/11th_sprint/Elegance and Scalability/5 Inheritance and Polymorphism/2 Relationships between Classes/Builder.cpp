#include <cassert>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class House {
    int length = 0;
    int width = 0;
    int height = 0;
    public:
    House(int l, int w, int h)
    {
        length = l;
        width = w;
        height = h;
    }
    int GetLength() const
    {
        return length;
    }
    int GetWidth() const 
    {
            return width;
    }
    int GetHeight() const
    {
            return height;
    }
};

class Resources {
    int bricks;
    public:
    Resources(int b): bricks(b){}
    void TakeBricks(int b)
    {
        if(b<0)
            throw std::out_of_range("attempt of taking negative number of bricks");
         if(b>bricks)
            throw std::out_of_range("attempt of taking more than available bricks");
        bricks-=b;
    }
    
    int GetBrickCount() const 
    {
        return bricks;
    }
    
    
};

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder {
    Resources* resources_;
    public:
    
    explicit Builder(Resources& r)
    {
        resources_ = &r;
    }
    
    
    
    House BuildHouse(HouseSpecification spec)
    {
        int requirement = 32 * spec.height * (spec.width + spec.length) * 2;
        if(requirement > resources_->GetBrickCount())
            throw std::runtime_error("builder doesnt have enough bricks");
        resources_->TakeBricks(requirement);
        return House(spec.length, spec.width, spec.height);
    }
};

int main() {
    Resources resources{10000};
    Builder builder1{resources};
    Builder builder2{resources};
    
    House house1 = builder1.BuildHouse(HouseSpecification{12, 9, 3});
    
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{8, 6, 3});
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{4, 3, 2});
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}
