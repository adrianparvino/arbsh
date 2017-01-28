#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <stdint.h>

#include "stdlib.h"
#include "unistd.h" 


int main (int argc, char *argv[]) 
{ 

	int integer = 0;
	double flt = 0;
	int i = 0;
	char string[4096] = { 0 };

	while ((i = getopt (argc, argv, "d:fsh")) != -1) 
		switch (i) {
			case 'd': 
				integer = gatoi(optarg);
				break;
			case 'f': 
				flt = gatof(optarg);
				break;
			case 's': 
				strcpy(string, optarg);
				break;
			case 'h':
				break; 
			default: 
				break;
		}

        argv += optind;
        argc -= optind;

	while ( *(argv) )
	{
		printf("%s\n",(*argv++));
	}
	printf("%lf\n", flt);
	printf("%d\n", integer);
	printf("%s\n", string);

	return 0;

}
