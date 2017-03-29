#include <gstdio.h> 

int gfputs(char *s, GFILE *fp)
{
	__puts_inter(s, fp, 0);
}
