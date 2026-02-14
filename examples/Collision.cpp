#include <BoltzMax/Physics.hpp>
#include <SFML/Graphics.hpp>

int main() {
    
    Environment *environment = new Environment(1920, 1080); Particle *selectedParticle = nullptr;
    
    sf::ContextSettings settings; settings.antialiasingLevel = 16;
    
    sf::RenderWindow window(sf::VideoMode(environment->getWidth(), environment->getHeight()), "Collision Simulation", sf::Style::Fullscreen); window.setVerticalSyncEnabled(true);
    
    for(int i = 1; i <= 27; i++) environment->addParticle();
    
    while(window.isOpen()) {
        
        sf::Event event;
        
        while(window.pollEvent(event)) {
            
            switch(event.type) {
                
                case sf::Event::MouseButtonPressed:
                    
                    if(event.mouseButton.button == sf::Mouse::Left) { float x = event.mouseButton.x, y = event.mouseButton.y; selectedParticle = environment->getParticle(x, y); }
                    
                    break;
                    
                case sf::Event::MouseButtonReleased:
                    
                    if(event.mouseButton.button == sf::Mouse::Left) selectedParticle = nullptr; break;
                    
                case sf::Event::KeyPressed:
                    
                    if(event.key.code == sf::Keyboard::Escape) window.close(); break;
                    
            }
            
        }
        
        environment->update(1.7f); if(selectedParticle) { float x = sf::Mouse::getPosition(window).x, y = sf::Mouse::getPosition(window).y; selectedParticle->moveTo(x, y, deltaTime); }
        
        window.clear(); std::vector<Particle*> particles = environment->getParticles();
        
        for(std::size_t i = 0; i < particles.size(); i++) {
            
            Particle *particle = particles[i]; sf::CircleShape circle(particle->getSize()); circle.setOrigin(particle->getSize(), particle->getSize()); circle.setPosition(particle->getX(), particle->getY()); window.draw(circle);
            
        }
        
        window.display();
        
    }
    
    return EXIT_SUCCESS;
    
}