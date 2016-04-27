#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

/* 
	Copyright 2015, C. Graff, `cat'
*/ 

int concatenate(int);

int main(int argc, char *argv[])
{ 

	if ( argc == 1 ) 
		concatenate(1); 
        while  (*++argv) 
		concatenate(open(*argv, O_RDONLY)); 
	return 0; 
} 


int concatenate(int source)
{

        ssize_t n = 0;
        char buf[4096];

        if ( source == -1 )
                return -1;

        while ((n = read(source, buf, 4096)) > 0)
	{
		if ( n < 0 )
			return -1;
                write(1, buf, n);
	}

	if (source != 1)
        	close(source);

	return 1;
}

