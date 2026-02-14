#include <BoltzMax/Physics/Environment.hpp>
#include <random>

Environment::Environment(float width, float height, float stability, Vector2 gravity): quadTree(), acceleration(gravity), width(width), height(height), stability(stability), elasticity(0.8f), airMass(0.2f), allowAcceleration(true), allowAttraction(false), allowBounce(true), allowCollision(true), allowCombination(false), allowDrag(true), allowMovement(true), lines(), springs(), particles(), collidables() {
    
    quadTree = new QuadTree(RectShape(0.f, 0.f, width, height), 8u, 4u);
    
}

Environment::~Environment() { for(std::size_t i = 0; i < lines.size(); i++) delete lines[i]; for(std::size_t i = 0; i < springs.size(); i++) delete springs[i]; for(std::size_t i = 0; i < particles.size(); i++) delete particles[i]; }

void Environment::setAirMass(float airMass) { this->airMass = airMass; }

void Environment::setElasticity(float elasticity) { this->elasticity = elasticity; }

void Environment::setAllowDrag(bool allowDrag) { this->allowDrag = allowDrag; }

void Environment::setAllowBounce(bool allowBounce) { this->allowBounce = allowBounce; }

void Environment::setAllowMovement(bool allowMovement) { this->allowMovement = allowMovement; }

void Environment::setAllowCollision(bool allowCollision) { this->allowCollision = allowCollision; }

void Environment::setAllowAttraction(bool allowAttraction) { this->allowAttraction = allowAttraction; }

void Environment::setAllowCombination(bool allowCombination) { this->allowCombination = allowCombination; }

void Environment::setAllowAcceleration(bool allowAcceleration) { this->allowAcceleration = allowAcceleration; }

void Environment::bounce(Particle *particle) {
    
    if(particle->getX() < particle->getSize()) { particle->setX(2.f * particle->getSize() - particle->getX()); particle->setAngle(PI - particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
    else if(particle->getX() > width - particle->getSize()) { particle->setX(2.f * (width - particle->getSize()) - particle->getX()); particle->setAngle(PI - particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
    if(particle->getY() < particle->getSize()) { particle->setY(2.f * particle->getSize() - particle->getY()); particle->setAngle(-1.f * particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
    else if(particle->getY() > height - particle->getSize()) { particle->setY(2.f * (height - particle->getSize()) - particle->getY()); particle->setAngle(-1.f * particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
}

void Environment::removeSpring(Spring *spring) { for(std::size_t i = 0; i < springs.size(); i++) if(springs[i] == spring) { delete springs[i]; springs.erase(springs.begin() + i); } }

void Environment::removeParticle(Particle *particle) { for(std::size_t i = 0; i < particles.size(); i++) if(particles[i] == particle) { delete particles[i]; delete collidables[i]; particles.erase(particles.begin() + i); collidables.erase(collidables.begin() + i); } }

void Environment::update(float sim_deltaTime, float acc_deltaTime, float gravConstant, float spring_deltaTime) {
    
    for(std::size_t i = 0; i < collidables.size(); i++) { Collidable *collidable = collidables[i]; collidable->bounds.x = particles.at(i)->getX(); collidable->bounds.y = particles.at(i)->getY(); quadTree->update(collidable); }
    
    for(std::size_t i = 0; i < particles.size(); i++) {
        
        Particle *particle_1 = particles[i];
        
        if(allowAcceleration) particle_1->accelerate(acceleration, acc_deltaTime);
        
        if(allowMovement) particle_1->move(sim_deltaTime);
        
        if(allowBounce) bounce(particle_1);
        
        if(allowDrag) particle_1->experienceDrag();
        
        if(std::fabs(particle_1->getSpeed()) < stability) { particle_1->setSpeed(0.f); particle_1->setAngle(0.f); }
        
        for(std::size_t j = i + 1; j < particles.size(); j++) {
            
            Particle *particle_2 = particles[j];
            
            if(collidables.at(i)->bounds.intersects(collidables.at(j)->bounds)) if(allowCollision) particle_1->checkCollision(particle_2);
            
            if(allowAttraction) particle_1->attract(particle_2, gravConstant);
            
            if(allowCombination) particle_1->combine(particle_2);
            
        }
        
    }
    
    for(std::size_t i = 0; i < lines.size(); i++) { Line *line = lines[i]; for(std::size_t j = 0; j < particles.size(); j++) { Particle *particle = particles[j]; if(allowCollision) line->checkCollision(particle); } }
    
    for(std::size_t i = 0; i < springs.size(); i++) { Spring *spring = springs[i]; spring->update(spring_deltaTime); }
    
}

Line* Environment::addLine(float startX, float startY, float endX, float endY, float width) { Line *line = new Line(startX, startY, endX, endY, width); lines.push_back(line); return line; }

Spring* Environment::addSpring(Particle* startParticle, Particle* endParticle, float length, float strength) { Spring *spring = new Spring(startParticle, endParticle, length, strength); springs.push_back(spring); return spring; }

Particle* Environment::addParticle() {
    
    std::random_device randomDevice; std::mt19937 randomEngine(randomDevice());
    
    std::uniform_int_distribution<int> sizeDistribution(10, 20); float size = sizeDistribution(randomDevice);
    
    std::uniform_real_distribution<float> massDistribution(100.f, 10000.f); float mass = massDistribution(randomDevice);
    
    std::uniform_real_distribution<float> xDistribution(size, width - size); float x = xDistribution(randomDevice);
    
    std::uniform_real_distribution<float> yDistribution(size, height - size); float y = yDistribution(randomDevice);
    
    std::uniform_real_distribution<float> speedDistribution(0.f, 1.f); float speed = speedDistribution(randomDevice);
    
    std::uniform_real_distribution<float> angleDistribution(0.f, 2.f * PI); float angle = angleDistribution(randomDevice);
    
    std::uniform_real_distribution<float> elasticityDistribution(0.8f, 1.f); float elasticity = elasticityDistribution(randomDevice);
    
    return addParticle(x, y, mass, size, angle, speed, elasticity);
    
}

Particle* Environment::addParticle(float x, float y, float mass, float size, float angle, float speed, float elasticity) {
    
    float drag = std::pow(mass / (mass + airMass), size); Particle *particle = new Particle(angle, drag, elasticity, mass, size, speed, x, y); Collidable *collidable = new Collidable(RectShape(x - 2.f * size, y - 2.f * size, 4.f * size, 4.f * size), size);
    
    quadTree->insert(collidable); collidables.push_back(collidable); particles.push_back(particle); return particle;
    
}

float Environment::getWidth() const { return width; }

float Environment::getHeight() const { return height; }

Line* Environment::getLine(float x, float y) const {
    
    for(std::size_t i = 0; i < lines.size(); i++)
        
        if(std::hypot(lines[i]->getStartX() - x, lines[i]->getStartY() - y) <= lines[i]->getWidth() || std::hypot(lines[i]->getEndX() - x, lines[i]->getEndY() - y) <= lines[i]->getWidth()) return lines[i];
        
    return nullptr;
    
}

Particle* Environment::getParticle(float x, float y) const {
    
    for(std::size_t i = 0; i < particles.size(); i++) if(std::hypot(particles[i]->getX() - x, particles[i]->getY() - y) <= particles[i]->getSize()) return particles[i];
    
    return nullptr;
    
}

std::vector<Line*> Environment::getLines() const { return lines; }

std::vector<Spring*> Environment::getSprings() const { return springs; }

std::vector<Particle*> Environment::getParticles() const { return particles; }

/* void Environment::bounce(Particle *particle) {
    
    if(particle->getX() < particle->getSize()) { particle->setX(2.f * particle->getSize() - particle->getX()); particle->setAngle(-1.f * particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
    else if(particle->getX() > width - particle->getSize()) { particle->setX(2.f * (width - particle->getSize()) - particle->getX()); particle->setAngle(-1.f * particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
    if(particle->getY() < particle->getSize()) { particle->setY(2.f * particle->getSize() - particle->getY()); particle->setAngle(PI - particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
    else if(particle->getY() > height - particle->getSize()) { particle->setY(2.f * (height - particle->getSize()) - particle->getY()); particle->setAngle(PI - particle->getAngle()); particle->setSpeed(particle->getSpeed() * particle->getElasticity()); }
    
} */