#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

/* error function */
void cutilerror(char *, int);

void cutilerror(char *message, int i)
{
        fprintf(stderr, "%s", message);
        if ( i > 0 )
                perror("Error: ");
	if ( i > -1 )
        	exit (i);
}
/* end error function */ 
