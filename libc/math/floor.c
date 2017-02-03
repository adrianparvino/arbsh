#include "math.h"

double myfloor(double x) 
{
	long i = (long)x; 
	if(i > x)
		--i; 
	return (double)i;
}
