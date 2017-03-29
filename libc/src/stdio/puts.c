#include <gstdio.h> 

int gputs(char *s)
{
	__puts_inter(s, gstdout, '\n');
}

