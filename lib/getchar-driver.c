#include <stdlib.h>
#include <unistd.h>

#include "stdio.h"


int simplecat(char *file)
{
	GFILE *fp = gfopen(file, "r");

	int c = 0;
	
	while (ggetc(fp) != GEOF )
		gputc(c, gstdout);
	gfclose(fp);
}

int main(int argc, char *argv[])
{
	simplecat(argv[1]);
}
