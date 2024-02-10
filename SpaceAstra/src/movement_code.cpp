#include "../headers/movement_code.h"
#include <cmath>

#define PI 3.14159265

void move_planets(float planet_data[5][8])
{
	for (int i = 0; i < 5; i++)
	{
		planet_data[i][0] = planet_data[i][0] + cos(planet_data[i][7]) * planet_data[i][6];
		planet_data[i][1] = planet_data[i][1] + sin(planet_data[i][7]) * planet_data[i][6];
		planet_data[i][4] = planet_data[i][6];
		planet_data[i][5] = planet_data[i][7];
	}
}
