#include <BoltzMax/Physics/RectShape.hpp>

float RectShape::getTop() const noexcept { return y + height / 2.f; }

float RectShape::getLeft() const noexcept { return x - width / 2.f; }

float RectShape::getRight() const noexcept { return x + width / 2.f; }

float RectShape::getBottom() const noexcept { return y - height / 2.f; }

bool RectShape::contains(const RectShape &shape) const noexcept {
    
    if(x > shape.x || y > shape.y || x + width < shape.x + shape.width || y + height < shape.y + shape.height) return false;
    
    return true;
    
}

bool RectShape::intersects(const RectShape &shape) const noexcept {
    
    if(x > shape.x + shape.width || y > shape.y + shape.height || x + width < shape.x || y + height < shape.y) return false;
    
    return true;
    
}