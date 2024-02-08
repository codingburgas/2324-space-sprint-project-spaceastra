#include<SFML/Graphics.hpp>
#include "../headers/space_rendering.h"

//function to render the planets
void draw_planets(sf::RenderWindow* window ,int arr[5][3])
{
	//loop that loops for every single planet (predetermined to be 5 max)
	for (int i = 0; i <= 5; i++)
	{
		// defining and rendering
		sf::CircleShape planet(arr[i][2]);
		planet.setFillColor(sf::Color::Green);
		planet.setOrigin(planet.getLocalBounds().width / 2, planet.getLocalBounds().height / 2);
		planet.setPosition(arr[i][0], arr[i][1]);

		window->draw(planet);

	}
}