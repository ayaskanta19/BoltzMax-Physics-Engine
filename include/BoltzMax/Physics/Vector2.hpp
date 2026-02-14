#pragma once

#ifndef BOLTZMAX_PHYSICS_VECTOR2_HPP
#define BOLTZMAX_PHYSICS_VECTOR2_HPP

#define PI 3.141592653589793238462643383f

#include <cmath>

struct Vector2 {
    
    Vector2(float speed, float angle): speed(speed), angle(angle) {}
    
    Vector2 operator+(const Vector2&); Vector2 operator*(float);
    
    float speed, angle;
    
};

#endif