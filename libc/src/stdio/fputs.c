#include <gstdio.h> 

int gfputs(char *  s, GFILE *  iop)
{
	int c;
	while ((c = *s++))
		gputc(c, iop);
	return gferror(iop) ? EOF : 0;
}

