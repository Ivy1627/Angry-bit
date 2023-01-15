/* Jingxin Zhang */

#include <stdio.h>

struct Bits;
struct Sim;

/* struct for bits */
typedef struct Bird
{
	unsigned short bits;
	double x, y;
	double vx, vy;
	int type;
	struct Sim *sim_ptr;
}Bird;

/* struct for sim */
typedef struct Sim
{
	int score;
	double time;
	struct Bird *bird_ptr;
	void *air_list;
	void *impact_list;
	FILE *file_ptr;
	int BONUS;
}Sim;
