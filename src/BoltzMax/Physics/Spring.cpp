#include <BoltzMax/Physics/Spring.hpp>

Spring::Spring(Particle *startParticle, Particle *endParticle, float length, float strength): startParticle(startParticle), endParticle(endParticle), length(length), strength(strength) {}

void Spring::update(float deltaTime) {
    
    float dx = endParticle->getX() - startParticle->getX(), dy = endParticle->getY() - startParticle->getY(), distance = std::hypot(dx, dy) - length, theta = -1.f * std::atan2(dy, dx), force = (length - distance) * strength;
    
    startParticle->accelerate(Vector2(force / startParticle->getMass(), theta + PI), deltaTime); endParticle->accelerate(Vector2(force / endParticle->getMass(), theta), deltaTime);
    
}

Particle* Spring::getEndParticle() const { return endParticle; }

Particle* Spring::getStartParticle() const { return startParticle; }

/* void Spring::update(float deltaTime) {
    
    float dx = startParticle->getX() - endParticle->getX(), dy = startParticle->getY() - endParticle->getY(), distance = std::hypot(dx, dy) - length, theta = std::atan2(dy, dx), force = (length - distance) * strength;
    
    startParticle->accelerate(Vector2(force / startParticle->getMass(), static_cast<float>(theta + PI / 2.f)), deltaTime); endParticle->accelerate(Vector2(force / endParticle->getMass(), static_cast<float>(theta - PI / 2.f)), deltaTime);
    
} */