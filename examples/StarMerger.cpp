#include <BoltzMax/Physics.hpp>
#include <SFML/Graphics.hpp>
#include <random>

int main() {
    
    Environment *environment = new Environment(1920, 1080, 0.5f, Vector2(981.f, -1.f * PI / 2.f));
    
    sf::ContextSettings settings; settings.antialiasingLevel = 16;
    
    sf::RenderWindow window(sf::VideoMode(environment->getWidth(), environment->getHeight()), "Star Merger Simulation", sf::Style::Fullscreen); window.setVerticalSyncEnabled(true);
    
    environment->setAllowDrag(false); environment->setAllowBounce(false); environment->setAllowCollision(false); environment->setAllowAttraction(true); environment->setAllowCombination(true); environment->setAllowAcceleration(false);
    
    std::random_device randomDevice; std::mt19937 randomEngine(randomDevice()); std::uniform_real_distribution<float> massDistribution(10.f, 50.f);
    
    float cameraX = 0.f, cameraY = 0.f, magnificationX = 0.f, magnificationY = 0.f, magnification = 1.f; bool paused = false;
    
    for(std::size_t i = 1; i <= 1000; i++) {
        
        float mass = massDistribution(randomDevice), size = 0.15f * std::pow(mass, 0.5f);
        
        std::uniform_real_distribution<float> xDistribution(size, environment->getWidth() - size); std::uniform_real_distribution<float> yDistribution(size, environment->getHeight() - size);
        
        environment->addParticle(xDistribution(randomDevice), yDistribution(randomDevice), mass, size);
        
    }
    
    while(window.isOpen()) {
        
        sf::Event event;
        
        while(window.pollEvent(event))
            
            if(event.type == sf::Event::KeyPressed) {
                
                if(event.key.code == sf::Keyboard::Left) cameraX += 0.2f * environment->getWidth() / (magnification * 10.f);
                
                else if(event.key.code == sf::Keyboard::Right) cameraX -= 0.2f * environment->getWidth() / (magnification * 10.f);
                
                else if(event.key.code == sf::Keyboard::Up) cameraY += 0.2f * environment->getHeight() / (magnification * 10.f);
                
                else if(event.key.code == sf::Keyboard::Down) cameraY -= 0.2f * environment->getHeight() / (magnification * 10.f);
                
                else if(event.key.code == sf::Keyboard::Add) { magnification *= 1.2f; magnificationX = (1.f - magnification) * environment->getWidth() / 2.f; magnificationY = (1.f - magnification) * environment->getHeight() / 2.f; }
                
                else if(event.key.code == sf::Keyboard::Subtract) { magnification *= 0.8f; magnificationX = (1.f - magnification) * environment->getWidth() / 2.f; magnificationY = (1.f - magnification) * environment->getHeight() / 2.f; }
                
                else if(event.key.code == sf::Keyboard::Return) { if(paused) paused = false; else paused = true; }
                
                else if(event.key.code == sf::Keyboard::Space) { cameraX = 0.f, cameraY = 0.f, magnificationX = 0.f, magnificationY = 0.f, magnification = 1.f; }
                
                else if(event.key.code == sf::Keyboard::Escape) window.close();
                
            }
            
        if(!paused) environment->update(deltaTime); window.clear(); std::vector<Particle*> particles = environment->getParticles();
        
        for(std::size_t i = 0; i < particles.size(); i++) {
            
            Particle *particle = particles[i]; if(particle->getCollisionPair()) { environment->removeParticle(particle->getCollisionPair()); particle->setSize(0.15f * std::pow(particle->getMass(), 0.5f)); }
            
            float x = magnificationX + (cameraX + particle->getX()) * magnification, y = magnificationY + (cameraY + particle->getY()) * magnification, size = particle->getSize() * magnification;
            
            sf::CircleShape circle(size); circle.setOrigin(size, size); circle.setPosition(x, y); window.draw(circle);
            
        }
        
        window.display();
        
    }
    
    return EXIT_SUCCESS;
    
}