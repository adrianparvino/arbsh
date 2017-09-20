#include <math.h>

extern int ___signgam;
double ___lgamma_r(double, int *);

double lgamma(double x)
{
	return ___lgamma_r(x, &___signgam);
}
