
/* Jingxin Zhang
 * parse_adjustments and adjustments are based on Professor Kibry's lab2 reference code */

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "constants.h"
#include "unsigned.h"
#include "struct.h"

#include "bits.h"
#include "output.h"
#include "memory.h"
#include "angry.h"
#include "linkedlist.h"
#include "callback.h"
#include "physics.h"

#include "input.h"

/* read bits and add it to the launcher if a hex is scanned */
void read_bits(Sim *p2sim)
{
	ushort bits;

	if(fscanf(p2sim->file_ptr, "%hx", &bits) == 1){
	    add_to_launcher(bits, p2sim);
	}
}

/* If the launcher is empty, read bits; otherwise make an adjustment */
void handle_input(Sim *p2sim)
{
	/* read in new bits in only when the bird pointer is free */
	if(p2sim->bird_ptr == NULL){
	    read_bits(p2sim);
	    if(p2sim->BONUS) clear_line(p2sim);
	}
	/* otherwise adjust bits */
	else{
	    adjust_bits(p2sim);
	}
}

/* parse the adjustment given the char */
ushort parse_adjustment(int adjustment, ushort bits)
{
	switch(adjustment)
	{
	    case '+':
		bits = increment_angle(bits);
	        break;

	    case '-':
		bits = decrement_angle(bits);
	        break;

	    case '>':
		bits = increment_force(bits);
	        break;

	    case '<':
		bits = decrement_force(bits);
	        break;

	    case ' ':
		break;

	    case '\n':
	    case EOF:
		bits = set_in_flight(bits);
		break;

	    default:
		;
		/* for now silently eat other characters */
	}
	return bits;
}

/* launch the bird */
void launch_bird(Bird *p2bird)
{
	p2bird->vx = get_vx(p2bird->bits);
	p2bird->vy = get_vy(p2bird->bits);
	add_to_air(p2bird);
}

/* read ajdustments in bonus */
int bonus_adjustment()
{
	int adjustment = ab_getch();

	/* TODO: how to check if there is no user input?? */
	if(!adjustment) {
	    return ERR;
	}
	else {
	    return adjustment;
	}
}

/* adjust bits in bonus */
void bonus_adjust(Bird *p2bird)
{	
	int adjustment = bonus_adjustment();
	if(adjustment == ERR){
	}
	/* if enter is hit? */
	else if(adjustment == '\n'){
	    launch_bird(p2bird);
	}
	else{ 
	    p2bird->bits = parse_adjustment(adjustment, p2bird->bits);
	}
}

/* adjust the bits and send it to the air list when finished */
void adjust_bits(Sim *p2sim)
{
	int adjustment;
	Bird *p2bird = p2sim->bird_ptr;

	if(p2sim->BONUS){
	    bonus_adjust(p2bird);
	}
	else{
	    adjustment = fgetc(p2sim->file_ptr);
	    p2bird->bits = parse_adjustment(adjustment, p2bird->bits);   
	    /* add the bird into the air list if set to in-air status */
	    if(in_air(p2bird)){
	        launch_bird(p2bird);
	    }
	}
}

/* clear the line until scanf hits EOF or new line */
void clear_line(Sim *p2sim)
{
	while (!feof(p2sim->file_ptr) && fgetc(p2sim->file_ptr) != (int)('\n'));
}
