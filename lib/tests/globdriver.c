#include <stdio.h>
#include "../glob.h"
#include <fnmatch.h>




int main(int argc, char **argv)
{
	if ( argc < 3 )
	{
		printf("Requires two args\n");
		return 1; 
	}

	++argv;

	if (gglob(*argv, *(argv + 1)))
		printf("Match|\n");
	else 
		printf("Not a match|\n");


	if (fnmatch(*argv, *(argv + 1), FNM_PERIOD) == 0)
                printf("Match|\n");
        else 
                printf("Not a match|\n");


	return 0;
}
