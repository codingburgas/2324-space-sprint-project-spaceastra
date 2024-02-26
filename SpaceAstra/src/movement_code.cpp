#include "../headers/movement_code.h"
#include <cmath>

#define PI 3.14159265

void move_planets(float planet_data[5][8])
{
	for (int i = 0; i < 5; i++)
	{
		//convert x and y of current velocity and the acceleration of the next frame
		float xcurrent = planet_data[i][4] * cos(planet_data[i][5] * PI / 180);
		float xnext = planet_data[i][6] * cos(planet_data[i][7] * PI / 180);
		float ycurrent = planet_data[i][4] * cos(planet_data[i][5] * PI / 180);
		float ynext = planet_data[i][6] * cos(planet_data[i][7] * PI / 180);


		//add the 2 velocities
		xcurrent += xnext;
		ycurrent += ynext;


		//convert the x and y into a total angle
		float total = atan2(xcurrent, ycurrent);
		if (total < 0)
		{
			total += PI * 2;
		}


		//convert the x and y into distance
		planet_data[i][4] = sqrt((xcurrent * xcurrent) + (ycurrent * ycurrent));

		//apply the new velocity to current frame vel
		planet_data[i][5] = total*(180/PI);
		

		planet_data[i][0] = planet_data[i][0] + (cos(planet_data[i][5]) * planet_data[i][4] * 0.1);
		planet_data[i][1] = planet_data[i][1] + (sin(planet_data[i][5]) * planet_data[i][4] * 0.1);
	}
}
