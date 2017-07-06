#include <math.h>

double pow(double x, double n)
{ 
	double y = 1;

	/* negative */
	if (n < 0)
		y = 1.0 / pow(x, -n);
	/* whole number */
	else if (n == (long long)n)
	{
		while (n--)
		      y *= x;
	}
	/* fractional */
	else
		y = exp(n * log(x)); 

	return y;
}

