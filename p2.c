/* Jingxin Zhang 
 * Prototype to test iterate */

#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "unsigned.h"
#include "node.h"
#include "linkedlist.h"

#include "p2.h"

/* test iterate */
void iterate_test(void *p2head, ActionFunction dothis)
{
	Node *p2traverse = p2head;
	while(p2traverse != NULL)
	{
	    dothis(p2traverse->data);
	    p2traverse = p2traverse->next;
	}
}

/* simply print the element */
static void print(void *data)
{
	Node *p2head = data;
	printf("address of the number: %d\n", p2head);
}

/* initialize a linked list {1,2,3}, return the pointer to head */
static Node* create_alist()
{
	int a,b,c;
	int *d1, *d2, *d3;
	Node *first, *second, *third = NULL;

	a = 1;
	b = 2;
	c = 3;

	d1 = &a;
	d2 = &b;
	d3 = &c;

	first = malloc(sizeof(Node));
	second = malloc(sizeof(Node));
	third = malloc(sizeof(Node));

	first->data = d1;
	first->next = second;

	second->data = d2;
	second->next = third;

	third->data = d3;
	third->next = NULL;

	return first;
}

/* print the address of the integer in the list node by node */
int main()
{
	Node *p2head = create_alist();
	iterate_test(p2head, print);

	return 0;
}
