#include "stringmath.h"

void setsign(char *s)
{
	if (s[0] == '+')
		s[0] = '-';
	else if (s[0] == '-')
		s[0] = '+';
	else 
		s[0] = '+';
}

