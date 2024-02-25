#include "../headers/physics_calculation.h"
#include <cmath>
#include <iostream>

#define PI 3.14159265

//calculates the force of attraction
float calc_attraction(int mass1, int mass2, float dist)
{
	return ((mass1 * mass2) / dist * dist)/mass1;
}

//calculates the position (x y coords) of the second object relative to the first
float calc_direction(int x1, int x2, int y1, int y2)
{
	float xdiff = x2 - x1;
	float ydiff = y2 - y1;
	float result = atan2(xdiff, ydiff);
	if (result < 0)
	{
		result += PI * 2;
	}
	return result;
}


//physics calculation that happens every frame
void physics_frame(float planet_data[5][8])
{
	std::cout << "next frame start" << std::endl;
	float velocity_bffr[5][5];
	float direction_bffr[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i != j)
			{
				int x1 = planet_data[i][0];
				int x2 = planet_data[j][0];
				int y1 = planet_data[i][1];
				int y2 = planet_data[j][1];
				int m1 = planet_data[i][3];
				int m2 = planet_data[j][3];
				velocity_bffr[i][j] = calc_attraction(m1, m2, sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0));
				direction_bffr[i][j] = calc_direction(x1, x2, y1, y2);
			}
		}
	}
	//these MIGHT get moved to a function
	//averages out angles
	for (int i = 0; i < 5; i++)
	{
		float s = 0;
		float c = 0;
		for (int j = 0; j < 5; j++)
		{
			if (i != j)
			{
				s = +sin(direction_bffr[i][j]);
				c = +cos(direction_bffr[i][j]);
			}
		}
		s /= 4;
		c /= 4;

		if (s > 0 && c > 0)
		{
			planet_data[i][7] = atan(s / c) * -180 / PI;
			std::cout << planet_data[i][7] << " " << i << std::endl;
		}
		else if (c < 0)
		{
			planet_data[i][7] = atan(s / c) * -180 / PI + 180;
			std::cout << planet_data[i][7] << " " << i << std::endl;
		}
		else if (s < 0 && c > 0)
		{
			planet_data[i][7] = atan(s / c) * -180 / PI + 360;
			std::cout << planet_data[i][7] << " " << i << std::endl;
		}

		//averages out speed
		float v = 0;
		for (int j = 0; j < 5; j++)
		{
			if (i != j)
			{
				v += velocity_bffr[i][j];
			}
		}
		v /= 4;
		//convert from meters to pixels
		v /= 100;
		std::cout << "velocity: " << v << std::endl;
		planet_data[i][6] = v;
	}
}