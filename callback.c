/* JIngxin Zhang */

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "unsigned.h"
#include "struct.h"
#include "node.h"

#include "linkedlist.h"
#include "list.h"
#include "bits.h"
#include "memory.h"
#include "output.h"
#include "physics.h"

#include "callback.h"

/* comparision function that compares x position of two birds */
int x_order(void *data1, void *data2)
{
	Bird *p2bird1 = data1;
	Bird *p2bird2 = data2;

	return (p2bird1->x > p2bird2->x);
}

/* comparision function that compares y position of two birds */
int y_order(void *data1, void *data2)
{
	Bird *p2bird1 = data1;
	Bird *p2bird2 = data2;

	return (p2bird1->y < p2bird2->y);
}

/* add bird to the air list and clear the launcher */
void add_to_air(Bird *p2bird)
{
	if(!insert(&p2bird->sim_ptr->air_list, p2bird, y_order, TEXT)){
	    fail_airinsertion(p2bird);
	    free_bird(p2bird);
	}
	/* TODO: launch messgage here */
	else{
	    launch_message(p2bird->bits);
	}

	/* clear the launcher */
	p2bird->sim_ptr->bird_ptr = NULL;
}

/* action function passed to deleteSome when removing a bird from the air list*/
void add_to_impact(void *data)
{
	Bird *p2bird = data;

	/* set the bits to impacted status*/
	p2bird->bits = set_to_impacted(p2bird->bits);

	if(!insert(&p2bird->sim_ptr->impact_list, p2bird, x_order, TEXT)){
	    fail_impactinsertion(p2bird);
	    free_bird(p2bird);
	}else{
	    /* else updates the score and print the impact message */
	    p2bird->sim_ptr->score += (int)p2bird->x;
	    impact_message(p2bird);
	}
}

/* criteria function to check if a bird is impacted */
int impacted(void *data)
{
	Bird *p2bird = data;
	return (p2bird->y < 0.0);
}

