#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/*
	Copyright 2015, C. Graff "link.c"
*/

int main(int argc, char *argv[])
{ 
	int error;

	if (argc == 3 )
	{
		if ( (link(argv[1], argv[2])) != 0)
		{
			error = errno;
			fprintf(stderr, "link() error number: %d\n", errno);
			perror("");
			return error;
		}
	}
	else
	{
		write(2, "Usage: link file1 file2\n", 24);
		return 1;
	}
	return 0;
}

