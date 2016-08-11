#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <ctype.h>

/*
	Copyright 2016, 'at.c', C. Graff 

	Conformance:
		Aligned with POSIX 2013
		All POSIX comments are quoted, the author's are not
*/

void at(char *, int []);

int main(int argc, char *argv[])
{ 
	int o = 0;
	int ret = EXIT_SUCCESS; 
	char *help = " \n";
	/*  options .. e  l  r */
	int opt[3] = {  };


	while ((o = getopt (argc, argv, "")) != -1)
		switch (o) { 
			case 'h':
                                if ( *argv )
                                        write(2, *argv, strlen(*argv));
                                write(2, help, strlen(help));
                                exit(ret);
			default:
				break;
		}

	argv += optind;
	argc -= optind;

	
	//if ( argc == 0 )
	//	;

	while ( *(argv) )
		at(*argv++, opt);
	
	return ret; 
}

void at(char *file, int opt[])
{
	
	
}
