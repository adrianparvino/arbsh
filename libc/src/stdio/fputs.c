#include <gstdio.h> 

int gfputs(char *s, GFILE *fp)
{
	return __puts_inter(s, fp, 0);
}
