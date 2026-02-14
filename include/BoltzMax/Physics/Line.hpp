#pragma once

#ifndef BOLTZMAX_PHYSICS_LINE_HPP
#define BOLTZMAX_PHYSICS_LINE_HPP

#include <BoltzMax/Physics/Particle.hpp>

class Line {
    
    public:
        
        Line(float, float, float, float, float);
        
        void setEndX(float);
        void setEndY(float);
        void setStartX(float);
        void setStartY(float);
        void checkCollision(Particle*);
        
        float getWidth() const;
        float getLength() const;
        
        float getEndX() const;
        float getEndY() const;
        float getStartX() const;
        float getStartY() const;
        
        Line* getCollisionPair() const;
        
    private:
        
        float startX, startY, endX, endY, width;
        
        Line *collisionPair;
        
};

float length(float, float, float, float);

#endif