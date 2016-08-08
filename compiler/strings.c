#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*
	Copyright 2016, "strings.c", C. Graff
*/

/*
	strings - find printable strings in files
*/

size_t strings(char *, size_t, char);

int main(int argc, char *argv[])
{ 
	int o = 0;
	size_t number = 0;
	char format = '\0';
	char *help = " [-a] [-t format] [-n number] [file...]\n";

        while ((o = getopt (argc, argv, "at:n:h")) != -1)
                switch (o) {
                        case 'a':
				break;
			case 't':
				if ( optarg && *optarg )
					format = *optarg;
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
		strings(NULL, number, format); 

	while ( *(argv) )
		strings(*argv++, number, format);

	return 0; 
}
size_t strings(char *file, size_t number, char format)
{
	int fd = STDIN_FILENO;

	if ( file )
	{
		if ( (fd = open(file, O_RDONLY)) == -1 )
		{
			return 0;
		}
	}
	
	switch(format){
		case 'd':
			break;
		case 'o':
			break;
		case 'x':
			break;
		default:
			break;
	}
	if (fd != STDIN_FILENO)
	{
		close(fd);
	}
	return 0; /* Change this to something useful */
}
