#pragma once

#ifndef BOLTZMAX_PHYSICS_PARTICLE_HPP
#define BOLTZMAX_PHYSICS_PARTICLE_HPP

#include <BoltzMax/Physics/Vector2.hpp>

class Particle {
    
    public:
        
        Particle(float, float, float, float, float, float, float, float);
        
        void experienceDrag();
        
        void setX(float);
        void setY(float);
        void setDrag(float);
        void setMass(float);
        void setSize(float);
        void setAngle(float);
        void setSpeed(float);
        void setElasticity(float);
        
        void move(float);
        void moveTo(float, float, float);
        
        void combine(Particle*);
        void checkCollision(Particle*);
        
        void attract(Particle*, float);
        void accelerate(Vector2, float);
        
        float getX() const;
        float getY() const;
        float getDrag() const;
        float getMass() const;
        float getSize() const;
        float getAngle() const;
        float getSpeed() const;
        float getElasticity() const;
        
        Particle* getCollisionPair() const;
        
    private:
        
        float angle, drag, elasticity, mass, size, speed, x, y;
        
        Particle *collisionPair;
        
};

#endif