
/* Jingxin Zhang
 * all graphics functions based on Professor Kirby's lab2 reference code */

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "constants.h"
#include "unsigned.h"
#include "struct.h"

#include "angry.h"
#include "linkedlist.h"
#include "memory.h"
#include "bits.h"
#include "physics.h"
#include "callback.h"
#include "output.h"

#define WAIT 4.0
#define MICROSLEEP 1000000


/******************* ground output *********************/
/* print the bird info after it hits the ground */
void print_ground(void *data){
	Bird *pt2bird = data;
        ushort hex = pt2bird->bits;

	printf("    %-7s at %4.3lf\n", get_color(pt2bird->type), pt2bird->x);
}

/* get the color given the type of a bird */
char* get_color(int type)
{
	char *names[] = {"Red", "Chuck", "Blues", "Bomb", "Matilda"};
	return names[type];
}

/* print the message when bird is successfully added to the launcher */
void print_add(ushort hex)
{
	printf("%hx added to the launcher\n", hex);
	load_message(hex);
}

/* print the bird info when it is in the launcher */
void print_launcher(Sim *p2sim)
{
	printf("Launcher:\n");
	if(p2sim->bird_ptr==NULL){
	    printf("    Nothing on the launcher.\n");
	}
	else{
	    ushort hex = p2sim->bird_ptr->bits;
	    printf("    %-7s at %2d deg %2d force\n", get_color(get_type(p2sim->bird_ptr->bits)), ANGLE_MULTIPLE * get_angle(hex), get_force(hex));
	}
}

/* output everything during the simulation */
void output_world(Sim *p2sim)
{
	if(TEXT) print_world(p2sim);
	if(GRAPHICS) draw_world(p2sim);
}

/* print everything during the simulation */
void print_world(Sim *p2sim)
{
	/* print time and the score at that time */
	print_score(p2sim);
	/* print the launcher */
	print_launcher(p2sim);
	/* print the air list */
	print_air_list(p2sim);
	/* print the impact list */
	print_impact_list(p2sim);
}

/* draw the whole simulation in the graphics mode */
void draw_world(Sim *p2sim)
{	
	ab_clear();
	ab_score(p2sim->score);
	draw_ground(p2sim->bird_ptr);
	iterate(p2sim->air_list, draw_air);
	iterate(p2sim->impact_list, draw_impact);
	ab_refresh();
	microsleep(( MICROSLEEP * DELTA_T));
}

/* generate the predicted flight trajectory markers 
 * Copyright: Kirby's lab3 reference predict function */
void predict(Bird *p2bird)
{
	p2bird->x = LAUNCH_X;
	p2bird->y = LAUNCH_Y;
	p2bird->vx = get_vx(p2bird->bits);
	p2bird->vy = get_vy(p2bird->bits);

	while(p2bird->y >=0.0){
	    ab_mark(p2bird->x, p2bird->y);
	    p2bird->x += p2bird->vx * DELTA_T;
	    p2bird->y += p2bird->vy * DELTA_T;
	    p2bird->vy += GRAVITY * DELTA_T;
	}
}

/* draw the predicted markers of adjiustments in graphics mode 
 * Copyright: based on Kirby's predict */
void draw_ground(Bird *p2bird)
{
	/* make a copy of the bird and reassign data to it each time it changes */
	Bird copy;
	if(p2bird){
	    ab_force(get_force(p2bird->bits));
	    ab_angle(get_angle(p2bird->bits)*ANGLE_MULTIPLE);

	    copy = *p2bird;
	    predict(&copy);
	    ab_bird(get_type(p2bird->bits), p2bird->x, p2bird->y);
	}
}

/*********************** air output **********************/
/* draw the position of the bits in the air */
void draw_air(void *data)
{
	Bird *pt2bird = data;
	
	ab_bird(pt2bird->type, pt2bird->x, pt2bird->y);
}

/* draw the position of the bits in the air */
void draw_impact(void *data)
{
	Bird *pt2bird = data;
	ab_bird(pt2bird->type, pt2bird->x, 0.0);
}

/* print the speed and position for a bird in the air list */
void print_movement(void *data)
{
	Bird *pt2bird = data;
	ushort hex = pt2bird->bits;

	printf("    %-8s at (%7.3lf, %7.3lf) moving (%7.3lf, %7.3lf)\n", get_color(get_type(pt2bird->bits)), pt2bird->x, pt2bird->y, pt2bird->vx, pt2bird->vy);
}

/* print the air list */
void print_air_list(Sim *p2sim)
{
	printf("In the air:\n");
	if(p2sim->air_list==NULL){
	    printf("    Nothing in the air\n");
	}
	else{
	    sort(p2sim->air_list, y_order);
	    iterate(p2sim->air_list, print_movement);
	}
}

/* print the score at a certain time */
void print_score(Sim *p2sim)
{
	printf("\nAt time %2.5lf the score is %d\n", p2sim->time, p2sim->score);
}

/* output the final world after clearing the impact list */
void final_world(Sim *p2sim)
{
	if(TEXT)print_world(p2sim);
	if(GRAPHICS){
	    iterate(p2sim->impact_list, draw_impact);
	    microsleep(MICROSLEEP * WAIT);
	}
}

/* message once a bird is loaded */
void load_message(ushort bits)
{
	if(TEXT) printf("Loaded %04X: type %2d at %2d deg %2d force\n",
	    bits, get_type(bits), ANGLE_MULTIPLE*get_angle(bits), get_force(bits));
	if(GRAPHICS)ab_status("Loaded new bits.");
}

/* messgae once a bird is ready to be launched */
void launch_message(ushort bits)
{
	if(TEXT) printf("Launched %04X: type %2d at %2d deg %2d force\n",
	    bits, get_type(bits), ANGLE_MULTIPLE*get_angle(bits), get_force(bits));
	if(GRAPHICS)ab_status("Launched new bits.");

}

/* message printed after a bird hits the ground */
void impact_message(void *data)
{
	Bird *p2bird = data;	
	if(TEXT)printf("IMPACT: %4X near X=%7.3lf\n", p2bird->bits, p2bird->x);
	if(GRAPHICS)ab_status("Impact!");
}

/* print the impact list */
void print_impact_list(Sim *p2sim)
{
        printf("Impacted:\n");
	if(p2sim->impact_list==NULL){
	    printf("    No impacts\n");
	}
	else{
	    iterate(p2sim->impact_list, print_ground);
	}
}

/******************diagnostic messages***********************/
/* print how many birds bave been freed */
void print_free(int num)
{
	printf("DIAGNOSTIC: %d birds freed.\n", num);
}

/* print how many birds have been allocated */
void print_allocation(int num)
{
	printf("DIAGNOSTIC: %d birds allocated.\n", num);
}

/*****************messages for clearing birds****************/
/* count how many birds are cleared from the impact list */
void clear_impact(Sim *p2sim)
{
	int count = deleteSome(&p2sim->impact_list, impacted, free_bird, TEXT);
	printf("%d birds cleared from impact list\n", count);
}

/* count how many birds are cleared from the launcher */
void clear_launcher(Sim *p2sim)
{
	int count = 0;
	if(p2sim->bird_ptr != NULL){
	    clear_bird(p2sim->bird_ptr);
	    count++;
	}
	printf("\n%d birds cleared from launcher\n", count);
}

/* count how many birds are cleared from the air list */
void clear_air(Sim *p2sim)
{
	int count = deleteSome(&p2sim->air_list, impacted, free_bird, TEXT);
	printf("%d birds cleared from air list\n", count);
}

/**********************error messages**************************/
/* error message for failure of bird allocation */
void allocate_launcher_error(ushort hex)
{	
	char* color = get_color(get_type(hex));
	printf("ERROR: add_to_launcher: malloc returned NULL\n");
	printf("ERROR: %s did not make to the launcher.\n", color);
}

/* failure of inserting a bird into air list */
void fail_airinsertion(Bird *p2bird)
{
	char *color = get_color(p2bird->type);
	printf("ERROR: Unable to insert into air list, Freeing bird\n");
	printf("ERROR: %s will be freed.\n", color);
}

/* failure of inserting a bird into impact list*/
void fail_impactinsertion(Bird *p2bird)
{
	char *color = get_color(p2bird->type);
	printf("ERROR: Unable to insert into impact list, Freeing bird\n");
	printf("ERROR: %s will be freed.\n", color);
}
