#include "math.h"

double gceil(double x) 
{

	long i = (long)x; 
	if(i < x)
		++i; 
	return (double)i; 
  
}

