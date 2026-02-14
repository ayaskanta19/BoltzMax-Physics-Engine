#include <BoltzMax/Physics/Line.hpp>

Line::Line(float startX, float startY, float endX, float endY, float width): startX(startX), startY(startY), endX(endX), endY(endY), width(width), collisionPair(nullptr) {}

void Line::setEndX(float endX) { this->endX = endX; }

void Line::setEndY(float endY) { this->endY = endY; }

void Line::setStartX(float startX) { this->startX = startX; }

void Line::setStartY(float startY) { this->startY = startY; }

void Line::checkCollision(Particle *particle) {
    
    float line_1X = endX - startX, line_1Y = endY - startY, line_2X = particle->getX() - startX, line_2Y = particle->getY() - startY;
    
    float edgeLength = getLength() * getLength(), section = std::fmax(0.f, std::fmin(edgeLength, (line_1X * line_2X + line_1Y * line_2Y))) / edgeLength;
    
    float closestPointX = startX + section * line_1X, closestPointY = startY + section * line_1Y;
    
    if(closestPointX + width + particle->getSize() > particle->getX() && particle->getX() + width + particle->getSize() > closestPointX && closestPointY + width + particle->getSize() > particle->getY() && particle->getY() + width + particle->getSize() > closestPointY) {
        
        float distance = length(closestPointX, closestPointY, particle->getX(), particle->getY());
        
        if(distance <= particle->getSize() + width) {
            
            float dx = closestPointX - particle->getX(), dy = closestPointY - particle->getY(), collisionAngle = -1.f * std::atan2(dy, dx), overlap = 0.7f * (particle->getSize() + width - distance + 1.f);
            
            distance = std::hypot(dx, dy); particle->setAngle(collisionAngle + PI); particle->setSpeed(particle->getSpeed() * particle->getElasticity());
            
            particle->setX(particle->getX() - overlap * std::cos(collisionAngle)); particle->setY(particle->getY() + overlap * std::sin(collisionAngle));
            
        }
        
        /* if(distance <= particle->getSize() + width) {
            
            float dx = closestPointX - particle->getX(), dy = closestPointY - particle->getY(), collisionAngle = PI / 2.f + std::atan2(dy, dx), overlap = 0.7f * (particle->getSize() + width - distance + 1.f);
            
            distance = std::hypot(dx, dy); particle->setAngle(collisionAngle - PI); particle->setSpeed(particle->getSpeed() * particle->getElasticity());
            
            particle->setX(particle->getX() - overlap * std::sin(collisionAngle)); particle->setY(particle->getY() + overlap * std::cos(collisionAngle));
            
        } */
        
        /* if(distance <= particle->getSize() + width) {
            
            float dx = closestPointX - particle->getX(), dy = closestPointY - particle->getY(), collisionAngle = -1.f * std::atan2(dy, dx), overlap = 0.7f * (particle->getSize() + width - distance);
            
            particle->setAngle(collisionAngle + PI); particle->setSpeed(particle->getSpeed() * particle->getElasticity());
            
            particle->setX(particle->getX() + overlap * (particle->getX() - closestPointX) / distance); particle->setY(particle->getY() + overlap * (particle->getY() - closestPointY) / distance);
            
        } */
        
    }
    
}

float Line::getWidth() const { return width; }

float Line::getLength() const { return length(startX, startY, endX, endY); }

float Line::getEndX() const { return endX; }

float Line::getEndY() const { return endY; }

float Line::getStartX() const { return startX; }

float Line::getStartY() const { return startY; }

Line* Line::getCollisionPair() const { return collisionPair; }

float length(float x_1, float y_1, float x_2, float y_2) { return std::sqrt((x_2 - x_1) * (x_2 - x_1) + (y_2 - y_1) * (y_2 - y_1)); }