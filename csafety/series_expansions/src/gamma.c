#include <math.h>

double lgamma(double x)
{
	return (log(fabs(gamma(x)))); 
}

double tgamma(double x)
{ 
	return gamma(x);
}

double gamma(double x)
{ 
        int a = 12;
        int k;
        double c[a];
        double fac = 1.0;
        double ret;

        ret = sqrt(2.0 * PI);

        for( k = 1; k < a ; k++)
        {
                c[k] = ((exp(a - k) * pow(a - k, k - 0.5)) / fac); 
                fac *= -k;
        }

        for( k = 1; k < a ; k++)
        {
                ret += (c[k] / (x + k));
        }

	/* -(x + a) */
        ret *= exp(-(x + a)) * pow(x + a, x + 0.5);

        return (ret / x);
}

