#include <math.h>
#include <stdio.h>
#define TOLER .0000000000000001
//              .3139443789225921377
//#define TOLER .000000000001
int _check_tolerance(double x, double y)
{
	if ( x > y - TOLER && x < y + TOLER )
	{
		fprintf(stderr, "tolerance met, breaking\n");
		return 1;
	}
	fprintf(stderr, "tolerance not yet met\n");
	return 0;
}
