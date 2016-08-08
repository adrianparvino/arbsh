#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*
	Copyright 2016, 'strings.c', C. Graff

	"strings - find printable strings in files"

	Conformance:
		Aligned with POSIX 2013
		All POSIX comments are quoted, the author's are not
*/ 


size_t strings(char *, size_t, char);

int main(int argc, char *argv[])
{ 
	int o = 0;
	size_t number = 3;
	char format = '\0';
	char *help = " [-a] [-t format] [-n number] [file...]\n";

	while ((o = getopt (argc, argv, "at:n:h")) != -1)
		switch (o) {
			case 'a': /* "Scan files in their entirety." */
				break;
			case 't': /* "Write each string preceded by its byte 
				      offset from the start of the file." */
				if ( optarg && *optarg )
					format = *optarg;
				break;
			case 'n':/* "Specify the minimum string length." */ 
				number = strtoul(optarg, 0, 10) - 1;
		 		break;
			case 'h':
				if ( *argv )
					write(2, *argv, strlen(*argv));
				write(2, help, strlen(help));
				exit(EXIT_SUCCESS);
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
	char *buffer;
	size_t i;
	int inastring;
	size_t j = 0;
	size_t offset = 0;
	char hold[1024];
	
	buffer = malloc(number * (sizeof buffer));

	if (!(buf = malloc(4096 * (sizeof buf))))
		return 0;

	if ( file )
	{
		if ( (fd = open(file, O_RDONLY)) == -1 )
		{
			return 0;
		}
	}
	i = inastring = 0;
	

	while ((ret = read(fd, buf, 4096)) > 0)
	{
		/* Add some error checking here */
		for (j = 0;j < ret ;j++, offset++)
		{
			buffer[i] = buf[j];
		
			if (!isprint(buffer[i]) && buffer[i] != '\t') {
				if (inastring)
					write(1, "\n", 1);
				inastring = 0;
				i = 0;

				continue;
			}
			if (i < number) {
				i++;
				continue;
			}
			if (!inastring) { 
				inastring = 1;
				size_t len = 0; 
				switch(format){
					case 'd': /* "The offset shall be written in decimal." */
						len = sprintf(hold, " %d %s", offset - number, buffer);
						break;
					case 'o': /* "The offset shall be written in octal." */
						len = sprintf(hold, " %o %s", offset - number, buffer);
						break;
					case 'x': /* "The offset shall be written in hexadecimal." */
						len = sprintf(hold, " %x %s", offset - number, buffer); 
						break;
					default:
						
						break;
				}
				
				write(1, hold, len);
				//write(1, buffer, strlen(buffer));
				continue;
			}
			
			write(1, buffer + i, 1); 
		}
	}

	/* not yet used */

	if (fd != STDIN_FILENO)
	{
		close(fd);
	}

	free(buffer);
	free(buf);

	return 0; /* Change this to something useful */
}
