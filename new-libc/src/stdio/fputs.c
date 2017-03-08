#include <gstdio.h> 

int gfputs(char * restrict s, GFILE * restrict iop)
{
	int c;
	while ((c = *s++))
		gputc(c, iop);
	return gferror(iop) ? EOF : 0;
}

