#include <stdlib.h>
#include <unistd.h>

#include "../stdio.h"


void simplecat(GFILE *fp)
{ 
	int c = 0;
	
	while (ggetc(fp) != GEOF )
		gputc(c, gstdout);
}

int main(int argc, char *argv[])
{
	if ( argc > 1 )
	{
		GFILE *fp = gfopen(argv[1], "r");
		simplecat(fp);
		gfclose(fp);
	}else {
		simplecat(gstdin);
	}
	return 0;
}
