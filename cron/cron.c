#include <unistd.h>
#include <stdlib.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <ctype.h>

/*
	Copyright 2016, 'cron.c', C. Graff 
*/

int main(int argc, char *argv[])
{ 
	int o = 0;
	int ret = EXIT_SUCCESS;

	while ((o = getopt (argc, argv, "")) != -1)
		switch (o) { 
			default:
				break;
		}

	argv += optind;
	argc -= optind;

	//if ( argc == 0 )
	//	;

	//while ( *(argv) )
	//	*argv++;

	return ret; 
}
