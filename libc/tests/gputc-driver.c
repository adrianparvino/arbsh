#include <gstdlib.h>
#include <gunistd.h>
#include <gstdio.h>


void simplecat(GFILE *fp)
{ 
	int c = 0;
	
	while ((c = ggetc(fp)) != -1 ) 
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
