#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
	Copyright 2016, 'strings.c', C. Graff

	"strings - find printable strings in files'

	Conformance:
		Aligned with POSIX 2013
		All POSIX comments are quoted, the author's are not
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
	ssize_t ret = 0;
	char *buf;
	size_t rotate = 0;
	int inaword = 0;

	if (!(buf = malloc(4096 * (sizeof buf))))
		return 0;

	if ( file )
	{
		if ( (fd = open(file, O_RDONLY)) == -1 )
		{
			return 0;
		}
	}
	
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		rotate = ret;
		write(1, buf, ret);
	}
	
	switch(format){
		case 'd': /* "The offset shall be written in decimal." */
			break;
		case 'o': /* "The offset shall be written in octal." */
			break;
		case 'x': /* "The offset shall be written in hexadecimal." */
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
