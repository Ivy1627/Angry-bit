/* Jingxin Zhang 
 * prototype to test tersed insert */

#include <stdio.h>
#include <stdlib.h>

#include "unsigned.h"
#include "struct.h"
#include "node.h"
#include "memory.h"
#include "debug.h"
#include "linkedlist.h"

#include "p1.h"

/* working functin from p2.c */
static void iterate_test(void *p2head, ActionFunction dothis)
{
        Node *p2traverse = p2head;
	while(p2traverse != NULL)
	{
	    dothis(p2traverse->data);
	    p2traverse = p2traverse->next;
	}
}


/* insert */
int insert_test(void *p2head, void *data, ComparisonFunction order, int text)
{
	/* set the pointer to p2node to change as the head pointer */
	Node **p2p2change = p2head;

	/* create a new node that contains pointer to data */
	Node *new_node = malloc(sizeof(Node));

	if(new_node){
	    /* assign data to the node */
	    new_node->data = data;

	    /* skip nodes with data of the wrong order regarding the data to insert*/
	    while(*p2p2change!=NULL && !order(data, ((**p2p2change).data)))
	    {
	        p2p2change = &((**p2p2change).next);
	    }
	    new_node->next = *p2p2change;
	    *p2p2change = new_node;

	    return 1;
	}

	else{return 0;}
}

/* are not running */
int main()
{
	printf("this prototype is not working");
	return 0;
}
