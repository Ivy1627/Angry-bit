/* Jingxin Zhang 
 * prototype for insert and sort */

#include <stdlib.h>
#include <stdio.h>
#include "unsigned.h"
#include "struct.h"
#include "node.h"
#include "linkedlist.h"
#include "list.h"

#include "p4.h"

/* sort test */
void sort_test(void *p2head, ComparisonFunction cf)
{
	int swapped;
	Node *p2traverse = p2head;
	do{
	    swapped = 0;
	    while(p2traverse!=NULL && p2traverse->next!=NULL){
	        if(!cf(p2traverse->data, p2traverse->next->data)){
		    swap(p2traverse, p2traverse->next);
		    swapped = 1;
		}
		p2traverse = p2traverse->next;
	    }
	    p2traverse = NULL;
	}while(swapped);
}

/* swap test */
void swap(void *data1, void *data2)
{	
	Node *node1 = data1;
	Node *node2 = data2;

	void *tmp = node1->data;
	node1->data = node2->data;
	node2->data = tmp;
}

/* cf to sort strings in alphebetical increasing order */
int alphabetical_order(void *data1, void *data2)
{
	char *str1 = data1;
	char *str2 = data2;
	return (str1[0] < str2[0]);
}

/* cf to sort strings in alphabetical decreasing order */
int alphabetical_order2(void *data1, void *data2)
{
	char *str1 = data1;
	char *str2 = data2;
	return (str1[0] > str2[0]);
}


/* print the string in the list */
void print_string(void *data)
{
	char *str = data;
	printf("%s\n", str);
}

/* sort a linked list of strings in alphebetical increasing order */
int main()
{	
	/* create a null pointer of node as the initial list */
	Node *list = NULL;
	/* build list of strings in alphabetical increasing order */
	printf("before sorting:\n");
	insert(&list, "apple", alphabetical_order, 1);
	insert(&list, "banana", alphabetical_order, 1);
	insert(&list, "orange", alphabetical_order, 1);
	iterate(list, print_string);
	/* sort it to be in the alphabetical decreasing order */
	sort(list, alphabetical_order2);
	printf("\nafter sorting:\n");
	iterate(list, print_string);
	return 0;
}
