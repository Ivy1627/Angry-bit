/* Jingxin Zhang */

#include <stdio.h>
#include <stdlib.h>

#include "p5.h"

/* open the file using the second argument entered */
FILE* openFile(char **argv)
{
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp){
	    printf("Successfully opened %s for reading\n", argv[1]);
	}
	else{
	    printf("ERROR: Unable to open %s for reading\n", argv[1]);
	}
	return fp;
}

/* test open file */
int main(int argc, char *argv[])
{
	FILE *fp = openFile(argv[1]);
	return 0;
}
