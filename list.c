/* Jingxin Zhang */

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "node.h"
#include "linkedlist.h"
#include "altmem.h"

#include "list.h"


/* allocate a node, return the pointer to the node */
static struct Node* allocate_node(int text)
{
	static int count = 0;
	Node *p2head = alternative_malloc(sizeof(Node));
	if(p2head){
	    count++;
	    if(text) printf("DIAGNOSTIC: %d nodes allocated.\n", count);
	}
	else{
	    if(text) printf("ERROR: list.c: Failed to allocate a Node.\n");
	}
	return p2head;
}

/* free a node */
static int free_node(void *data, int text)
{
	static int count = 0;	
	alternative_free(data);
	count++;
	if(TEXT) printf("DIAGNOSTIC: %d nodes freed.\n", count);
	return count;
}

/* returns if the node is successfully inserted according to the given order * (using tersed insert) */
int insert(void *p2head, void *data, ComparisonFunction order, int text)
{
	/* set the pointer to p2node to change to as the head pointer */
	Node **p2p2change = p2head, *p2new_node = allocate_node(text);
	
	if(p2new_node){
	    p2new_node->data = data;
	    while(*p2p2change!=NULL && !order(data, (**p2p2change).data))
	    {
	        /* make the pointer to p2change point to its next node*/
	        p2p2change = &((**p2p2change).next);   
	    }
	    p2new_node->next = *p2p2change;
	    *p2p2change = p2new_node;

	    return 1;
	}
	else{return 0;}
}

/* returns the total number deleted given the critetria 
 * (using tersed delete) */
int deleteSome(void *p2head, CriteriaFunction mustGo, ActionFunction disposal, int text)
{
	int count;
	Node **p2p2change = p2head, *p2holder;
	while(*p2p2change){
	    if(mustGo((**p2p2change).data)){
	        /*delete_helper(p2holder, p2p2change);*/
		p2holder = *p2p2change;
		*p2p2change = p2holder->next;
		disposal(p2holder->data);
		free_node(p2holder, text);
		count++;
	    }
	    else{p2p2change = &(**p2p2change).next;}
	}
	return count;
}

/* swap data in p2node1 and p2node2 (not swapping nodes) */
static void swap(void *data1, void *data2)
{
	Node *node1 = data1;
	Node *node2 = data2;

	Node *tmp = node1->data;
	node1->data = node2->data;
	node2->data = tmp;
}


/* helper function used in sort to determine if data in two nodes should be swapped */
static void determine_swap(Node *p2traverse, int swapped, ComparisonFunction cf)
{
	if(!cf(p2traverse->data, p2traverse->next->data)){
	    swap(p2traverse, p2traverse->next);
	    swapped = 1;
	}
}

/* sort the linked list in the given order 
 * code structure based on GeekstoGeeks bubble sort on linked list */
void sort(void *p2head, ComparisonFunction cf)
{
	int swapped;
	Node *p2traverse = p2head;
	do{
	    swapped = 0;
	    while(p2traverse!=NULL && p2traverse->next!=NULL){
	    	determine_swap(p2traverse, swapped, cf);
	        /* increase the traverse pointer */
		p2traverse = p2traverse->next;
	    }
	    p2traverse = NULL;
	}while(swapped);
}

/* impose the action on each node in the linked list */
void iterate(void *p2head, ActionFunction doThis)
{
	/* set the pointer to the traverse node to point to the head */
	Node *p2traverse = p2head;
	/* traverse till the end of the list */
	while(p2traverse != NULL)
	{
	    doThis(p2traverse->data);
	    /* increse the traverse pointer by 1 */
	    p2traverse = p2traverse->next;
	}
}
