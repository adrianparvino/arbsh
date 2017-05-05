#include <gmath.h>
#include <gstddef.h>

double gexp(double x)
{
	size_t i;
	size_t n = 2;
	double y = 1.0 + x;
	double d = 0;
	double last = 0;

	if (x == 1.0) 
		return EULER;
	else if (x < 0) 
		return 1.0 / gexp(-x); 
	

	for ( ; 1 ; n++)
	{
		d = x;
		for (i = 2; i <= n; i++)
		{
			d *= x / i; 
		}
		y += d;

		if (_check_tolerance(last, y))
			break;
		last = y;
	}
	
	return y;
}


