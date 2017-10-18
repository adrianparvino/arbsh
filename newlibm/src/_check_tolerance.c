#include <math.h>
#include <stdio.h>
#include <float.h>
//#define TOLER .0000000000000001
#define TOLER .000000000000000001

int _check_tolerance(double x, double y)
{
	if ( x == y )
		return 1;
	else
		return 0;
	if ( x >= y - TOLER && x <= y + TOLER )
	{
		fprintf(stderr, "tolerance met, breaking x=%19.19lf   y=%19.19lf\n", x, y);
		return 1;
	}
	fprintf(stderr, "tolerance not yet met x=%19.19lf   y=%19.19lf\n", x, y);
	return 0;
}
