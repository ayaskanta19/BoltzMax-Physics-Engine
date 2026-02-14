#include <BoltzMax/Physics/Vector2.hpp>

Vector2 Vector2::operator+(const Vector2 &vector) {
    
    float x = speed * std::cos(angle) + vector.speed * std::cos(vector.angle), y = speed * std::sin(angle) + vector.speed * std::sin(vector.angle); return Vector2(std::hypot(x, y), std::atan2(y, x));
    
}

Vector2 Vector2::operator*(float scalar) { return Vector2(scalar * speed, angle); }

/* Vector2 Vector2::operator+(const Vector2 &vector) {
    
    float x = speed * std::sin(angle) + vector.speed * std::sin(vector.angle), y = speed * std::cos(angle) + vector.speed * std::cos(vector.angle); return Vector2(std::hypot(x, y), static_cast<float>(PI / 2.f - std::atan2(y, x)));
    
} */