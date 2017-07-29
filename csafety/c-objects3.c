#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 


typedef struct{ 
        char *rp; 
	size_t len;
} object;


int main(void)
{ 
	size_t i = 0;
	size_t lim = 10;

	/* create an array of objects */
	object o[10];

	/* allocate memory for and populate the members of the array of objects */
	for ( ; i < lim ; ++i) 
	{
		(o+i)->rp = malloc(1024);
		(o+i)->len = sprintf((o+i)->rp, "string %zu\n", i); 
	}

	/* test the array of objects (fast write!) */
	for (i=0 ; i < lim ; ++i)
		write(1, (o+i)->rp, (o+i)->len); 

	for (i=0 ; i < lim ; ++i)
		free((o+i)->rp);

	return 0; 
}

