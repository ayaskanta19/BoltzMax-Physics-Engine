#include <BoltzMax/Physics.hpp>
#include <SFML/Graphics.hpp>

int main() {
    
    Environment *environment = new Environment(1920, 1080); Particle *selectedParticle = nullptr;
    
    sf::ContextSettings settings; settings.antialiasingLevel = 16;
    
    sf::RenderWindow window(sf::VideoMode(environment->getWidth(), environment->getHeight()), "Soft Body Simulation", sf::Style::Fullscreen); window.setVerticalSyncEnabled(true);
    
    float mass = 600.f, size = 10.f, angle = 0.f, speed = 0.f, elasticity = 0.1f, length = 50.f, strength = 20.f;
    
    Particle *particle_11 = environment->addParticle(200, 600, mass, size, angle, speed, elasticity);
    Particle *particle_12 = environment->addParticle(300, 600, mass, size, angle, speed, elasticity);
    Particle *particle_13 = environment->addParticle(400, 700, mass, size, angle, speed, elasticity);
    Particle *particle_14 = environment->addParticle(400, 800, mass, size, angle, speed, elasticity);
    Particle *particle_15 = environment->addParticle(300, 900, mass, size, angle, speed, elasticity);
    Particle *particle_16 = environment->addParticle(200, 900, mass, size, angle, speed, elasticity);
    Particle *particle_17 = environment->addParticle(100, 800, mass, size, angle, speed, elasticity);
    Particle *particle_18 = environment->addParticle(100, 700, mass, size, angle, speed, elasticity);
    
    environment->addSpring(particle_11, particle_12, length, strength);
    environment->addSpring(particle_11, particle_13, length, strength);
    environment->addSpring(particle_11, particle_14, length, strength);
    environment->addSpring(particle_11, particle_15, length, strength);
    environment->addSpring(particle_11, particle_16, length, strength);
    environment->addSpring(particle_11, particle_17, length, strength);
    environment->addSpring(particle_11, particle_18, length, strength);
    environment->addSpring(particle_12, particle_13, length, strength);
    environment->addSpring(particle_12, particle_14, length, strength);
    environment->addSpring(particle_12, particle_15, length, strength);
    environment->addSpring(particle_12, particle_16, length, strength);
    environment->addSpring(particle_12, particle_17, length, strength);
    environment->addSpring(particle_12, particle_18, length, strength);
    environment->addSpring(particle_13, particle_14, length, strength);
    environment->addSpring(particle_13, particle_15, length, strength);
    environment->addSpring(particle_13, particle_16, length, strength);
    environment->addSpring(particle_13, particle_17, length, strength);
    environment->addSpring(particle_13, particle_18, length, strength);
    environment->addSpring(particle_14, particle_15, length, strength);
    environment->addSpring(particle_14, particle_16, length, strength);
    environment->addSpring(particle_14, particle_17, length, strength);
    environment->addSpring(particle_14, particle_18, length, strength);
    environment->addSpring(particle_15, particle_16, length, strength);
    environment->addSpring(particle_15, particle_17, length, strength);
    environment->addSpring(particle_15, particle_18, length, strength);
    environment->addSpring(particle_16, particle_17, length, strength);
    environment->addSpring(particle_16, particle_18, length, strength);
    environment->addSpring(particle_17, particle_18, length, strength);
    
    Particle *particle_21 = environment->addParticle(600, 400, mass, size, angle, speed, elasticity);
    Particle *particle_22 = environment->addParticle(700, 400, mass, size, angle, speed, elasticity);
    Particle *particle_23 = environment->addParticle(800, 500, mass, size, angle, speed, elasticity);
    Particle *particle_24 = environment->addParticle(800, 600, mass, size, angle, speed, elasticity);
    Particle *particle_25 = environment->addParticle(700, 700, mass, size, angle, speed, elasticity);
    Particle *particle_26 = environment->addParticle(600, 700, mass, size, angle, speed, elasticity);
    Particle *particle_27 = environment->addParticle(500, 600, mass, size, angle, speed, elasticity);
    Particle *particle_28 = environment->addParticle(500, 500, mass, size, angle, speed, elasticity);
    
    environment->addSpring(particle_21, particle_22, length, strength);
    environment->addSpring(particle_21, particle_23, length, strength);
    environment->addSpring(particle_21, particle_24, length, strength);
    environment->addSpring(particle_21, particle_25, length, strength);
    environment->addSpring(particle_21, particle_26, length, strength);
    environment->addSpring(particle_21, particle_27, length, strength);
    environment->addSpring(particle_21, particle_28, length, strength);
    environment->addSpring(particle_22, particle_23, length, strength);
    environment->addSpring(particle_22, particle_24, length, strength);
    environment->addSpring(particle_22, particle_25, length, strength);
    environment->addSpring(particle_22, particle_26, length, strength);
    environment->addSpring(particle_22, particle_27, length, strength);
    environment->addSpring(particle_22, particle_28, length, strength);
    environment->addSpring(particle_23, particle_24, length, strength);
    environment->addSpring(particle_23, particle_25, length, strength);
    environment->addSpring(particle_23, particle_26, length, strength);
    environment->addSpring(particle_23, particle_27, length, strength);
    environment->addSpring(particle_23, particle_28, length, strength);
    environment->addSpring(particle_24, particle_25, length, strength);
    environment->addSpring(particle_24, particle_26, length, strength);
    environment->addSpring(particle_24, particle_27, length, strength);
    environment->addSpring(particle_24, particle_28, length, strength);
    environment->addSpring(particle_25, particle_26, length, strength);
    environment->addSpring(particle_25, particle_27, length, strength);
    environment->addSpring(particle_25, particle_28, length, strength);
    environment->addSpring(particle_26, particle_27, length, strength);
    environment->addSpring(particle_26, particle_28, length, strength);
    environment->addSpring(particle_27, particle_28, length, strength);
    
    Particle *particle_31 = environment->addParticle(1300, 400, mass, size, angle, speed, elasticity);
    Particle *particle_32 = environment->addParticle(1400, 400, mass, size, angle, speed, elasticity);
    Particle *particle_33 = environment->addParticle(1500, 500, mass, size, angle, speed, elasticity);
    Particle *particle_34 = environment->addParticle(1500, 600, mass, size, angle, speed, elasticity);
    Particle *particle_35 = environment->addParticle(1400, 700, mass, size, angle, speed, elasticity);
    Particle *particle_36 = environment->addParticle(1300, 700, mass, size, angle, speed, elasticity);
    Particle *particle_37 = environment->addParticle(1200, 600, mass, size, angle, speed, elasticity);
    Particle *particle_38 = environment->addParticle(1200, 500, mass, size, angle, speed, elasticity);
    
    environment->addSpring(particle_31, particle_32, length, strength);
    environment->addSpring(particle_31, particle_33, length, strength);
    environment->addSpring(particle_31, particle_34, length, strength);
    environment->addSpring(particle_31, particle_35, length, strength);
    environment->addSpring(particle_31, particle_36, length, strength);
    environment->addSpring(particle_31, particle_37, length, strength);
    environment->addSpring(particle_31, particle_38, length, strength);
    environment->addSpring(particle_32, particle_33, length, strength);
    environment->addSpring(particle_32, particle_34, length, strength);
    environment->addSpring(particle_32, particle_35, length, strength);
    environment->addSpring(particle_32, particle_36, length, strength);
    environment->addSpring(particle_32, particle_37, length, strength);
    environment->addSpring(particle_32, particle_38, length, strength);
    environment->addSpring(particle_33, particle_34, length, strength);
    environment->addSpring(particle_33, particle_35, length, strength);
    environment->addSpring(particle_33, particle_36, length, strength);
    environment->addSpring(particle_33, particle_37, length, strength);
    environment->addSpring(particle_33, particle_38, length, strength);
    environment->addSpring(particle_34, particle_35, length, strength);
    environment->addSpring(particle_34, particle_36, length, strength);
    environment->addSpring(particle_34, particle_37, length, strength);
    environment->addSpring(particle_34, particle_38, length, strength);
    environment->addSpring(particle_35, particle_36, length, strength);
    environment->addSpring(particle_35, particle_37, length, strength);
    environment->addSpring(particle_35, particle_38, length, strength);
    environment->addSpring(particle_36, particle_37, length, strength);
    environment->addSpring(particle_36, particle_38, length, strength);
    environment->addSpring(particle_37, particle_38, length, strength);
    
    Particle *particle_41 = environment->addParticle(1600, 600, mass, size, angle, speed, elasticity);
    Particle *particle_42 = environment->addParticle(1700, 600, mass, size, angle, speed, elasticity);
    Particle *particle_43 = environment->addParticle(1800, 700, mass, size, angle, speed, elasticity);
    Particle *particle_44 = environment->addParticle(1800, 800, mass, size, angle, speed, elasticity);
    Particle *particle_45 = environment->addParticle(1700, 900, mass, size, angle, speed, elasticity);
    Particle *particle_46 = environment->addParticle(1600, 900, mass, size, angle, speed, elasticity);
    Particle *particle_47 = environment->addParticle(1500, 800, mass, size, angle, speed, elasticity);
    Particle *particle_48 = environment->addParticle(1500, 700, mass, size, angle, speed, elasticity);
    
    environment->addSpring(particle_41, particle_42, length, strength);
    environment->addSpring(particle_41, particle_43, length, strength);
    environment->addSpring(particle_41, particle_44, length, strength);
    environment->addSpring(particle_41, particle_45, length, strength);
    environment->addSpring(particle_41, particle_46, length, strength);
    environment->addSpring(particle_41, particle_47, length, strength);
    environment->addSpring(particle_41, particle_48, length, strength);
    environment->addSpring(particle_42, particle_43, length, strength);
    environment->addSpring(particle_42, particle_44, length, strength);
    environment->addSpring(particle_42, particle_45, length, strength);
    environment->addSpring(particle_42, particle_46, length, strength);
    environment->addSpring(particle_42, particle_47, length, strength);
    environment->addSpring(particle_42, particle_48, length, strength);
    environment->addSpring(particle_43, particle_44, length, strength);
    environment->addSpring(particle_43, particle_45, length, strength);
    environment->addSpring(particle_43, particle_46, length, strength);
    environment->addSpring(particle_43, particle_47, length, strength);
    environment->addSpring(particle_43, particle_48, length, strength);
    environment->addSpring(particle_44, particle_45, length, strength);
    environment->addSpring(particle_44, particle_46, length, strength);
    environment->addSpring(particle_44, particle_47, length, strength);
    environment->addSpring(particle_44, particle_48, length, strength);
    environment->addSpring(particle_45, particle_46, length, strength);
    environment->addSpring(particle_45, particle_47, length, strength);
    environment->addSpring(particle_45, particle_48, length, strength);
    environment->addSpring(particle_46, particle_47, length, strength);
    environment->addSpring(particle_46, particle_48, length, strength);
    environment->addSpring(particle_47, particle_48, length, strength);
    
    environment->addLine(963.f, 100.f, 300.f, 300.f, 5.f);
    environment->addLine(963.f, 200.f, 200.f, 500.f, 5.f);
    environment->addLine(1620.f, 300.f, 957.f, 100.f, 5.f);
    environment->addLine(1720.f, 500.f, 957.f, 200.f, 5.f);
    
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
        
        environment->update(1.f); if(selectedParticle) { float x = sf::Mouse::getPosition(window).x, y = sf::Mouse::getPosition(window).y; selectedParticle->moveTo(x, y, deltaTime); }
        
        window.clear(); std::vector<Line*> lines = environment->getLines(); std::vector<Spring*> springs = environment->getSprings();
        
        for(std::size_t i = 0; i < lines.size(); i++) {
            
            Line *line = lines[i]; sf::RectangleShape shape(sf::Vector2f(line->getLength(), line->getWidth() * 2.f)); shape.setOrigin(0.f, line->getWidth()); shape.setPosition(line->getStartX(), line->getStartY());
            
            shape.setRotation(std::atan2(line->getEndY() - line->getStartY(), line->getEndX() - line->getStartX()) * 180.f / PI); window.draw(shape);
            
        }
        
        for(std::size_t i = 0; i < springs.size(); i++) {
            
            Spring *spring = springs[i]; sf::Vertex line[] = { sf::Vertex(sf::Vector2f(spring->getStartParticle()->getX(), spring->getStartParticle()->getY())), sf::Vertex(sf::Vector2f(spring->getEndParticle()->getX(), spring->getEndParticle()->getY())) };
            
            window.draw(line, 2, sf::Lines);
            
        }
        
        window.display();
        
    }
    
    return EXIT_SUCCESS;
    
}