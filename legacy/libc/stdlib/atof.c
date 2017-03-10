#include "stdlib.h"

double gatof(const char *s)
{
	double val, power;
	static size_t i = 0;
	size_t sign = 0;
	if (gisspace(*s))
		gatof(s + ++i);
	//for (i = 0; gisspace(s[i]); i++)
		//;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; gisdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; gisdigit(s[i]); i++) 
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}
