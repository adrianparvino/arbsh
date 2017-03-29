#include <gstdio.h> 

int gputs(char *s)
{
	return __puts_inter(s, gstdout, '\n');
}

