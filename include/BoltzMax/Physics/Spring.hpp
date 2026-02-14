#pragma once

#ifndef BOLTZMAX_PHYSICS_SPRING_HPP
#define BOLTZMAX_PHYSICS_SPRING_HPP

#include <BoltzMax/Physics/Particle.hpp>

class Spring {
    
    public:
        
        Spring(Particle*, Particle*, float restLength = 50.f, float strength = 20.f);
        
        void update(float);
        
        Particle* getEndParticle() const;
        Particle* getStartParticle() const;
        
    private:
        
        Particle *endParticle; Particle *startParticle;
        
        float length, strength;
        
};

#endif