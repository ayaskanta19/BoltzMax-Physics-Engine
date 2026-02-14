#pragma once

#ifndef BOLTZMAX_PHYSICS_ENVIRONMENT_HPP
#define BOLTZMAX_PHYSICS_ENVIRONMENT_HPP

#include <BoltzMax/Physics/Line.hpp>
#include <BoltzMax/Physics/Spring.hpp>
#include <BoltzMax/Physics/QuadTree.hpp>

class Environment {
    
    public:
        
        Environment(float, float, float stability = 0.04f, Vector2 acceleration = Vector2(9.8f, -1.f * PI / 2.f));
        // Environment(float, float, float stability = 0.04f, Vector2 acceleration = Vector2(9.8f, PI));
        
        ~Environment();
        
        void update(float, float acc_deltaTime = 0.02f, float gravConstant = 10.f, float spring_deltaTime = 1.f);
        
        void setAirMass(float);
        void setElasticity(float);
        
        void setAllowDrag(bool);
        void setAllowBounce(bool);
        void setAllowMovement(bool);
        void setAllowCollision(bool);
        void setAllowAttraction(bool);
        void setAllowCombination(bool);
        void setAllowAcceleration(bool);
        
        void bounce(Particle*);
        
        void removeSpring(Spring*);
        void removeParticle(Particle*);
        
        Line* addLine(float, float, float, float, float);
        Spring* addSpring(Particle*, Particle*, float restLength = 50.f, float strength = 20.f);
        
        Particle* addParticle();
        Particle* addParticle(float, float, float mass = 100.f, float size = 10.f, float angle = 0.f, float speed = 0.f, float elasticity = 0.9f);
        
        float getWidth() const;
        float getHeight() const;
        
        Line* getLine(float, float) const;
        Particle* getParticle(float, float) const;
        
        std::vector<Line*> getLines() const;
        std::vector<Spring*> getSprings() const;
        std::vector<Particle*> getParticles() const;
        
    private:
        
        QuadTree *quadTree; Vector2 acceleration;
        
        const float width, height, stability; float elasticity, airMass;
        
        bool allowAcceleration, allowAttraction, allowBounce, allowCollision, allowCombination, allowDrag, allowMovement;
        
        std::vector<Line*> lines; std::vector<Spring*> springs; std::vector<Particle*> particles; std::vector<Collidable*> collidables;
        
};

#endif