/* Jingxin Zhang */

#include <stdio.h>
#include <stdlib.h>

#include "unsigned.h"
#include "struct.h"
#include "constants.h"
#include "debug.h"

#include "linkedlist.h"
#include "altmem.h"
#include "physics.h"
#include "output.h"
#include "input.h"
#include "bits.h"
#include "memory.h"

/* fill the fields for a bird given a hex number and add it to the sim structure */
void create_bird(ushort hex, Sim *p2sim)
{
	if(p2sim->bird_ptr){
	    p2sim->bird_ptr->bits = hex;
	    p2sim->bird_ptr->type = get_type(hex);
	    p2sim->bird_ptr->sim_ptr = p2sim;
	    p2sim->bird_ptr->x = LAUNCH_X;
	    p2sim->bird_ptr->y = LAUNCH_Y;
	}
}

/* allocate space for a bird and allocate it to the launcher */
void add_to_launcher(ushort hex, Sim *p2sim)
{
	static int count = 0;
	p2sim->bird_ptr = alternative_malloc(sizeof(Bird));
			     
	/* check if malloc succeeds */
	if (p2sim->bird_ptr!=NULL){
	    create_bird(hex, p2sim);
	    count++;
	    print_allocation(count);
	    print_add(hex);
	}
	else {
	    allocate_launcher_error(hex);
	    clear_line(p2sim);
	}
}

/* free the space for a bird from the sim structure */
void free_bird(void *data)
{	
	Bird *p2bird = data;
	static int count = 0;
	alternative_free(p2bird);
	count++;
	print_free(count);
}

/* completely clear a bird by setting it to null */
void clear_bird(void *data)
{
	Bird *p2bird = data;
	free(p2bird);
	p2bird = NULL;

}
