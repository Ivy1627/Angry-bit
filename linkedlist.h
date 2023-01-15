

/* header file for list */

/* these are the function pointer signatures needed */

typedef void (* ActionFunction)( void *data);
typedef int (* ComparisonFunction)(void *data1, void *data2);
typedef int (* CriteriaFunction)(void *data);
typedef double (* NumericFunction)(void *data);


/* signatures that the list code provides to the outside world */

/* insert and delete need to be able to change the head pointer so you pass
 * in the address of the head pointer */

/* insert returns FALSE when it fails to do the insert */
int insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, 
		int text);
/* deleteSome returns the count of how many nodes were deleted. */
int deleteSome(void *p2head, CriteriaFunction mustGo, 
		ActionFunction disposal, int text);

/* The rest do not change the nodes, so you pass in the head
 * pointer and not the address of the head pointer */

/* call do this on everyitem in the list */
void iterate(void *head, ActionFunction doThis);

/* do at least some of the things in the list meet the criteria? */
int some(void *head, CriteriaFunction someTest);

/* sort the list based on your function */
void sort(void *hptr, ComparisonFunction cf);

/* return the smallest numeric value computed, NaN if empty list. */
double least(void *head, NumericFunction compute_this);

