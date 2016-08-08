#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/*
	Copyright 2016, "strings.c", C. Graff
*/

/*
	strings - find printable strings in files
*/

size_t strings(char *, size_t, char *);

int main(int argc, char *argv[])
{ 
	int o = 0;
	size_t number = 0;
	char *format = NULL;
	char *help = " [-a] [-t format] [-n number] [file...]\n";

        while ((o = getopt (argc, argv, "at:n:h")) != -1)
                switch (o) {
                        case 'a':
				break;
			case 't':
				break;
			case 'n':
				number = strtoll(optarg, 0, 10);
                       		break;
			case 'h':
				if ( *argv )
					write(2, *argv, strlen(*argv));
				else
					write(2, "strings", 7);
				write(2, help, strlen(help));
				exit(0); /* EXIT_SUCCESS */
                        default:
                                break;
                }

        argv += optind;
        argc -= optind;

	if ( argc == 0 )
		strings(0, number, format); /* STDIN_FILENO */

	while ( *(argv) )
		strings(*argv++, number, format);

	return 0; 
}
size_t strings(char *fd, size_t number, char *format)
{
	
	return 0; /* Change this to something useful */
}
