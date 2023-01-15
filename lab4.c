/* Jingxin Zhang 
 * Code based on Professor Kirby's lab2 reference code */

#include <stdlib.h>
#include <stdio.h>

#include "unsigned.h"
#include "debug.h"
#include "angry.h"
#include "constants.h"
#include "struct.h"

#include "node.h"
#include "linkedlist.h"
#include "list.h"
#include "callback.h"
#include "bits.h"
#include "input.h"
#include "physics.h"
#include "output.h"
#include "memory.h"
#include "lab4.h"

/* initialize the graphics */
int init()
{
	return (TEXT || ( GRAPHICS && ab_initialize()));
}

/* tear down the graphics */
void teardown()
{
	if(GRAPHICS)ab_teardown();
}

/* run the program properly in both text and graphics modes */
void run_compatible(Sim *p2sim)
{
	if(init())
	{	
	    run_sim(p2sim);
	    teardown();
	}
}

/* open the file */
int open_file(int argc, char *argv[], Sim *p2sim)
{
	FILE *fp = fopen(argv[1], "r");
	if(fp){
	    p2sim->file_ptr = fp;
	    printf("DIAGNOSTIC: Successfully opened %s for reading.\n", argv[1]);
	    /* set the bonus flag to 1 if argc is 3 */
	    if(argc==3) p2sim->BONUS = 1;
	    return 1;
	}
	else{
	    printf("ERROR: Unable to open %s for reading.\n", argv[1]);
	    return 0;
	}
}

/* check if bonus mode should be run */
void run_bonus(Sim *p2sim)
{
	if(GRAPHICS){
	    run_compatible(p2sim);
	}
	else{
	    printf("ERROR: Bonus mode cannot be run in text mode\n");
	}
}

/* run normal/bonus or print error given the number of argc */
void check_argc(int num, Sim *p2sim)
{
	if(num <= 1){
	    printf("ERROR: Insufficient arguments (arg is 1)\n");
	}
	else if(num >= 3){
	    run_bonus(p2sim);
	}
	else{
	    run_compatible(p2sim);
	}
}

/* main: total time takes to run the simulation */
int main(int argc, char *argv[])
{
	double start = now(), runtime;
	Sim initial_sim = {0, 0.0, NULL, NULL, NULL, NULL, 0};
	Sim *p2sim = &initial_sim;
	int file_exists = open_file(argc, argv, p2sim);
	if(file_exists) check_argc(argc, p2sim);
	runtime = now()- start;
	/* close the file only when file is opened */
	if(p2sim->file_ptr) close_file(p2sim);

	printf("Total run time is %.9lf seconds.\n", runtime);

	return(0);
}

/* close file */
void close_file(Sim *p2sim)
{
	fclose(p2sim->file_ptr);
	printf("DIAGNOSTIC: Input file closed.\n");
}

/* run_sim: as long as there's stuff to do , run the simulation*/
void run_sim(Sim *p2sim)
{
	while (!stop_sim(p2sim)){
	    /* output the world */
	    output_world(p2sim);
	    /* change the world */
	    change_world(p2sim);
	}
	/* print the final world again */
	final_world(p2sim);
	/* free all the birds */
	clear_everything(p2sim);
}

/* every DELTA_T seconds, change the world */ 
void change_world(Sim *p2sim)
{
	/* clock tick */
	p2sim->time += DELTA_T;
	/* handle input */
	handle_input(p2sim);
	/* move the birds in the air list*/
	iterate(p2sim->air_list, update_coordinates);
	/* move bird from the air list to the impact list if impacted */
	deleteSome(&p2sim->air_list, impacted, add_to_impact, TEXT);
}

/* stop the simulation when launcher and both lists are empty*/
int stop_sim(Sim *p2sim)
{
	return (feof(p2sim->file_ptr) && p2sim->air_list==NULL && p2sim->bird_ptr==NULL);
}

/* clear all the birds at the end of the simulation */
void clear_everything(Sim *p2sim)
{
	clear_launcher(p2sim);
	clear_air(p2sim);
	clear_impact(p2sim);
}
