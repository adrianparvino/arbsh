#include <gmath.h>

double gexp(double x)
{
	size_t j = 0;
	size_t i = 2;
	double sum = 1.0 + x;
	double product = 0;
	double last = 0;

	if (x == 1.0) 
		return EULER;
	else if (x < 0) 
		return 1.0 / gexp(-x); 
	

	for ( ; i < 10 ; i++)
	{
		product = x;
		for (j = 2; j <= i; j++) 
			product *= x / j; 
		
		sum += product;

		if (_check_tolerance(last, sum))
			break;

		last = sum;
	}
	
	return sum;
}


