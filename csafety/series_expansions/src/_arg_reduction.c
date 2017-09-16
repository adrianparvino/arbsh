#include <math.h>

double _arg_reduction(double x)
{
        while ( x >= (2*PI))
                x -= (2*PI);
        while ( x < 0 )
                x += (2*PI);
	return x;
}

