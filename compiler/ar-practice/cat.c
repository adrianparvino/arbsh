
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int concatenate(int); 

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

