#include <math.h>

double remainder(double x, double y)
{ 
	double ret;

	if ( x < 0.0 )
		return x;

	if ( y < 0.0  )
                y = -y;

	ret = x - (y * floor(x / y)); 

	return ret; 
}
