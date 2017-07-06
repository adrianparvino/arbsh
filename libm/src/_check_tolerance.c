#include <math.h>

int _check_tolerance(double x, double y)
{
	if ( x > y - TOLER && x < y + TOLER )
		return 1;
	return 0;
}
