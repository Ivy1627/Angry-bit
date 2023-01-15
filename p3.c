/* Jingxin Zhang
 * Prototype to test deleteSome */

#include <stdio.h>
#include <stdlib.h>

#include "unsigned.h"
#include "linkedlist.h"

#include "node.h"

#include "p3.h"

/* test deleteSome */
int deleteSome_test(void *p2head, CriteriaFunction mustGo, ActionFunction disposal, int text)
{
	int count = 0;
	/* holder is to store the pointer to the node to change */
	Node **p2p2change = p2head, *holder;

	while(*p2p2change != NULL){
	    /* the node to be deleted is the node after the node to be changed */
	    if(mustGo((**p2p2change).data)){
	        holder = *p2p2change;
	    	/* set pointer to p2change to point to the next node */
		*p2p2change = holder->next;
		/* call disposal on the data */
		disposal(holder->data);
		/* free the node to delete */
	    	free(holder);
		++count;
	    }
	    /* skip nodes with data that should be kept */
	    else{
	        p2p2change = &(**p2p2change).next;
	    }

	}

	return count;
}

/* criterian function to determine if a string starts with h */
int startwith_h(void *data)
{
	char *string = data; 
	if(string[0] == 'h'){
	    return 1;
	}
	else{return 0;}
}

/* print the string */
static void print(void *data)
{
	char *str = data;
	printf("%s\n", str);
}

/* alphabetical order */
int alphabetical(void *data1, void *data2)
{
	char *str1 = data1;
	char *str2 = data2;
	return (str1[0] > str2[0]);
}

/* test delete hellos */
int main()
{
	Node *p2head = NULL;
	insert(&p2head, "hello", alphabetical, 1);
	insert(&p2head, "apple", alphabetical, 1);
	insert(&p2head, "orange", alphabetical, 1);
	printf("before deletion:\n");
	iterate(p2head, print);
	deleteSome_test(&p2head, startwith_h, print, 1);
	printf("after deletion:\n");
	iterate(p2head, print);
	return 0;
}
