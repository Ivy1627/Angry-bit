/* Jingxin Zhang */

#include <stdio.h>
#include <math.h>

#include "unsigned.h"
#include "constants.h"
#include "struct.h"
#include "bits.h"
#include "physics.h"

#define FLAT_ANGLE 180.0

/* get the velocity of a bird in the x direction */
double get_vx(ushort hex)
{
	double V = get_force(hex);
	double radians = ANGLE_MULTIPLE*get_angle(hex) * M_PI / FLAT_ANGLE;

	double VX = V * cos(radians);

	return(VX);
}

/* get the velocity of a bird in the y direction */
double get_vy(ushort hex)
{
	double V = get_force(hex);
	double radians = ANGLE_MULTIPLE*get_angle(hex) * M_PI / FLAT_ANGLE;

	double VY = V * sin(radians);

	return(VY);
}

/* update positions of a bird */
void update_coordinates(void *data)
{
	Bird *pt2bird = data;
	pt2bird->x += pt2bird->vx * DELTA_T;
	pt2bird->y += pt2bird->vy * DELTA_T;
	pt2bird->vy += GRAVITY * DELTA_T;

}

/* set the launch data of a bird, copyright Kirby */
void set_launch_data(Bird *p2bird)
{
	p2bird->x = LAUNCH_X;
	p2bird->x = LAUNCH_Y;
	p2bird->vx = get_vx(p2bird->bits);
	p2bird->vy = get_vy(p2bird->bits);
}
