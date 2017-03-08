#include "math.h"

double myceil(double x) 
{

	long i = (long)x; 
	if(i < x)
		++i; 
	return (double)i; 
  
}

