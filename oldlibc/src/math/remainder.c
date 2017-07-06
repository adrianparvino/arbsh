#include <gmath.h>

double gremainder(double x, double y)
{ 
	double ret;

	if ( x < 0.0 )
		return x;

	if ( y < 0.0  )
                y = -y;

	ret = x - (y * gfloor(x / y)); 

	return ret; 
}
