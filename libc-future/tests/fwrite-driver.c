#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <gstdio.h>

int main(int argc, char *argv[])
{
	char buffer[BUFSIZ] = { 0 };
	int c = 0;
	ssize_t ret = 0; 
	if ( argc > 1 ) 
	{
		GFILE *filepointer = gfopen(argv[1], "r"); 
		while ( (ret = gfread(buffer, 1, 1000, filepointer)) > 0 )
			gfwrite(buffer, 1, ret, gstdout);
		gfclose(filepointer);
	}
	return 0;
}

