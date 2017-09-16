#include <math.h>

double ceil(double x) 
{

	long i = (long)x; 
	if(i < x)
		++i; 
	return (double)i; 
  
}

