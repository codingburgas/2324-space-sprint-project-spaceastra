#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/space_rendering.h"
#include "../headers/physics_calculation.h"
#include "../headers/movement_code.h"

//array 0 is x coord
//array 1 is y coord
//array 2 is radius
//array 3 is mass
//array 4 is velocity
//array 5 is direction
//array 6 is next frame velocity
//array 7 is next frame direction of velocity

float planet_data[5][8] =
{
    { 100, 100, 30, 5, 6, 300, 0, 0 },
    { 500, 300, 50, 40, 3, 500, 0, 0  },
    { 300, 500, 40, 33, 5, 400, 0, 0  },
    { 200, 140, 10, 20, 30, 100, 0, 0  },
    { 930, 700, 100, 80, 20, 10000, 0, 0  }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SpaceAstra", sf::Style::Close);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
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
        physics_frame(planet_data);
        std::cout << planet_data[1][7] << " " << 2 << std::endl;
        move_planets(planet_data);
        std::cout << planet_data[1][7] << std::endl;
        window.clear();
        draw_planets(&window, planet_data);
        window.display();
    }

}