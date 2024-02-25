#include <SFML/Graphics.hpp>

bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return rect1.intersects(rect2);
} 

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Collision Detection");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the items or change their positions here...

        // Check for collision
        if (checkCollision(planet.getGlobalBounds(), planet.getGlobalBounds())) {
            planet.move(1, 1);
        }
    }
}