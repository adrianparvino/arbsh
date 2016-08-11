#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <ctype.h>

/*
	Copyright 2016, 'crontab.c', C. Graff 
	
	"crontab - schedule periodic background work"

	Conformance:
		Aligned with POSIX 2013
		All POSIX comments are quoted, the author's are not
*/

int main(int argc, char *argv[])
{ 
	int o = 0;
	int ret = EXIT_SUCCESS; 
	char *help = " [-e|-l|-r]\n";


	while ((o = getopt (argc, argv, "elrh")) != -1)
		switch (o) {
			case 'e':
				break;
			case 'l':
				break;
			case 'r':
				break;
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

	//while ( *(argv) )
	//	*argv++;

	return ret; 
}
