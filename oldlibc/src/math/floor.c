#include <gmath.h>

double gfloor(double x) 
{
	long i = (long)x; 
	if(i > x)
		--i; 
	return (double)i;
}
