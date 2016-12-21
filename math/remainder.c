#include "math.h"

double myremainder(double x, double y)
{ 
	double ret;

	if ( x < 0.0 )
		return x;

	if ( y < 0.0  )
                y = -y;

	ret = x - (y * myfloor(x / y)); 

	return ret; 
}
