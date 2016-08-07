#include <unistd.h>

/*
	Copyright 2016, "strings.c", C. Graff
*/

size_t strings(char *);

int main(int argc, char *argv[])
{ 
	int o = 0;

        while ((o = getopt (argc, argv, "at:n:")) != -1)
                switch (o) {
                        case 'a':
				break;
			case 't':
				break;
			case 'n':
                       		break;
                        default:
                                break;
                }

        argv += optind;
        argc -= optind;

	if ( argc == 0 )
		strings(0); /* STDIN_FILENO */

	while ( *(argv) )
		strings(*argv++);

	return 0; 
}
size_t strings(char *fd) 
{
	return 0; /* Change this to something useful */
}
