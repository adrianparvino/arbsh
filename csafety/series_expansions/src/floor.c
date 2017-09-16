#include <math.h>

double floor(double x) 
{
	long i = (long)x; 
	if(i > x)
		--i; 
	return (double)i;
}
