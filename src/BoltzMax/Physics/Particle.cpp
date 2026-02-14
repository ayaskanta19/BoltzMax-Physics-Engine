#include <BoltzMax/Physics/Particle.hpp>

Particle::Particle(float angle, float drag, float elasticity, float mass, float size, float speed, float x, float y): angle(angle), drag(drag), elasticity(elasticity), mass(mass), size(size), speed(speed), x(x), y(y), collisionPair(nullptr) {}

void Particle::experienceDrag() { speed *= drag; }

void Particle::setX(float x) { this->x = x; }

void Particle::setY(float y) { this->y = y; }

void Particle::setDrag(float drag) { this->drag = drag; }

void Particle::setMass(float mass) { this->mass = mass; }

void Particle::setSize(float size) { this->size = size; }

void Particle::setAngle(float angle) { this->angle = angle; }

void Particle::setSpeed(float speed) { this->speed = speed; }

void Particle::setElasticity(float elasticity) { this->elasticity = elasticity; }

void Particle::move(float deltaTime) { x += speed * deltaTime * std::cos(angle); y -= speed * deltaTime * std::sin(angle); }

void Particle::moveTo(float x, float y, float deltaTime) { float dx = x - this->x, dy = y - this->y; speed = std::hypot(dx, dy) * deltaTime; angle = -1.f * std::atan2(dy, dx); }

void Particle::combine(Particle *particle) {
    
    float dx = x - particle->x, dy = y - particle->y, distance = std::hypot(dx, dy);
    
    if(distance < size + particle->size) {
        
        float totalmass = mass + particle->mass; x = (x * mass + particle->x * particle->mass) / totalmass; y = (y * mass + particle->y * particle->mass) / totalmass;
        
        Vector2 vector = Vector2(mass * speed / totalmass, angle) + Vector2(particle->mass * particle->speed / totalmass, particle->angle);
        
        speed = vector.speed * elasticity * particle->elasticity; angle = vector.angle; mass = totalmass; collisionPair = particle;
        
    }
    
}

void Particle::checkCollision(Particle *particle) {
    
    float dx = x - particle->x, dy = y - particle->y, distance = std::hypot(dx, dy);
    
    if(x + size + particle->size > particle->x && particle->x + size + particle->size > x && y + size + particle->size > particle->y && particle->y + size + particle->size > y)
        
        if(distance < size + particle->size) {
            
            float collisionAngle = -1.f * std::atan2(dy, dx), totalMass = mass + particle->mass;
            
            // float collisionAngle = PI / 2.f + std::atan2(dy, dx), totalMass = mass + particle->mass;
            
            Vector2 vector_1 = Vector2(speed * (mass - particle->mass) / totalMass, angle) + Vector2(particle->speed * 2.f * particle->mass / totalMass, collisionAngle);
            
            Vector2 vector_2 = Vector2(speed * 2.f * mass / totalMass, static_cast<float>(collisionAngle + PI)) + Vector2(particle->speed * (particle->mass - mass) / totalMass, particle->angle);
            
            speed = vector_1.speed; angle = vector_1.angle; particle->speed = vector_2.speed; particle->angle = vector_2.angle;
            
            float newElasticity = elasticity * particle->elasticity; speed *= newElasticity; particle->speed *= newElasticity;
            
            float overlap = (size + particle->size - distance + 0.1f) * 0.5f;
            
            x += overlap * std::cos(collisionAngle); y -= overlap * std::sin(collisionAngle); particle->x -= overlap * std::cos(collisionAngle); particle->y += overlap * std::sin(collisionAngle);
            
            // x += overlap * std::sin(collisionAngle); y -= overlap * std::cos(collisionAngle); particle->x -= overlap * std::sin(collisionAngle); particle->y += overlap * std::cos(collisionAngle);
            
        }
        
}

void Particle::attract(Particle *particle, float gravConstant) {
    
    float dx = x - particle->x, dy = y - particle->y, distance = std::hypot(dx, dy), theta = -1.f * std::atan2(dy, dx), force = mass * particle->mass / (distance * distance);
    
    accelerate(Vector2(force / mass, static_cast<float>(theta + PI)), gravConstant); particle->accelerate(Vector2(force / particle->mass, static_cast<float>(theta)), gravConstant);
    
}

void Particle::accelerate(Vector2 vector, float deltaTime) { Vector2 velocity = Vector2(speed, angle) + vector * deltaTime; speed = velocity.speed; angle = velocity.angle; }

float Particle::getX() const { return x; }

float Particle::getY() const { return y; }

float Particle::getDrag() const { return drag; }

float Particle::getMass() const { return mass; }

float Particle::getSize() const { return size; }

float Particle::getAngle() const { return angle; }

float Particle::getSpeed() const { return speed; }

float Particle::getElasticity() const { return elasticity; }

Particle* Particle::getCollisionPair() const { return collisionPair; }

// void Particle::move(float deltaTime) { x += speed * deltaTime * std::sin(angle); y -= speed * deltaTime * std::cos(angle); }

// void Particle::moveTo(float x, float y, float deltaTime) { float dx = x - this->x, dy = y - this->y; speed = std::hypot(dx, dy) * deltaTime; angle = PI / 2.f + std::atan2(dy, dx); }

/* void Particle::attract(Particle *particle, float gravConstant) {
    
    float dx = x - particle->x, dy = y - particle->y, distance = std::hypot(dx, dy), theta = std::atan2(dy, dx), force = mass * particle->mass / (distance * distance);
    
    accelerate(Vector2(force / mass, static_cast<float>(theta - PI / 2.f)), gravConstant); particle->accelerate(Vector2(force / particle->mass, static_cast<float>(theta + PI / 2.f)), gravConstant);
    
} */