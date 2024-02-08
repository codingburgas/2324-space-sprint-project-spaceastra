#include <SFML/Graphics.hpp>
#include "space_rendering.h"

int planet_data[5][3] =
{
    { 100, 100, 30 },
    { 500, 300, 50 },
    { 300, 500, 40 },
    { 200, 140, 10 },
    { 230, 900, 100 }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SpaceAstra", sf::Style::Close);
    window.setFramerateLimit(120);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i <= 5; i++)
        {
            planet_data[i][1] += 1;
            planet_data[i][0] += 1;
            if (planet_data[i][0] >= 1200)
                planet_data[i][0] = 0;
            if (planet_data[i][1] >= 800)
                planet_data[i][1] = 0;
        }

        window.clear();
        draw_planets(&window, planet_data);
        window.display();
    }

    return 0;
}