#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 

/*
	Copyright 2015, "head.c", C. Graff
*/

void cathead(int, size_t);

int main(int argc, char *argv[])
{ 
	int o;
	size_t lines;

	lines = 10;

        while ((o = getopt (argc, argv, "n:")) != -1)
                switch (o) {
                        case 'n':
                                lines = strtod(optarg, NULL);
                                break;
                        default:
                                break;
                }

        argv += optind;
        argc -= optind; 

	if ( argc == 0 )
                cathead(STDIN_FILENO, lines);

        while ( *(argv) ) 
		cathead(open(*argv++, O_RDONLY), lines); 

	return 0; 
}


void cathead(int source, size_t end)
{

        size_t i, j, k; 
	size_t len;
	char *buf; 
     
	len = BUFSIZ;

	if (!(buf = malloc(sizeof(char) * len)))
		return;

	i = j = k = 0;

        if ( source == -1 )
                return;

        while ((i = read(source, buf, len)) > 0)
        {
		j = 0;
                while (j < i)
                {
                        if ( buf[j] == '\n' )
                                ++k;
			++j; 
                        if ( k == end  )
				break; 
                }
		write (STDOUT_FILENO, buf, j);
        }
	
	free(buf);
        close(source);
}

