#pragma once

#ifndef BOLTZMAX_PHYSICS_RECTSHAPE_HPP
#define BOLTZMAX_PHYSICS_RECTSHAPE_HPP

struct RectShape {
    
    RectShape(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f): x(x), y(y), width(width), height(height) {}
    
    RectShape(const RectShape &shape): RectShape(shape.x, shape.y, shape.width, shape.height) {}
    
    float getTop() const noexcept;
    float getLeft() const noexcept;
    float getRight() const noexcept;
    float getBottom() const noexcept;
    
    bool contains(const RectShape&) const noexcept;
    bool intersects(const RectShape&) const noexcept;
    
    float x, y, width, height;
    
};

#endif