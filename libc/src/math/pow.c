#include <gmath.h>

double gpow(double x, double n)
{ 
	double y = 1;

	/* negative */
	if (n < 0)
		y = 1.0 / gpow(x, -n);
	/* whole number */
	else if (n == (long long)n)
	{
		while (n--)
		      y *= x;
	}
	/* fractional */
	else
		y = gexp(n * glog(x)); 

	return y;
}

