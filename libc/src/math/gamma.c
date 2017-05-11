#include <gmath.h>

double glgamma(double x)
{
	return (glog(gfabs(ggamma(x)))); 
}

double gtgamma(double x)
{ 
	return ggamma(x);
}

double ggamma(double x)
{ 
        int a = 12;
        int k;
        double c[a];
        double fac = 1.0;
        double ret;

        ret = gsqrt(2.0 * PI);

        for( k = 1; k < a ; k++)
        {
                c[k] = ((gexp(a - k) * gpow(a - k, k - 0.5)) / fac); 
                fac *= -k;
        }

        for( k = 1; k < a ; k++)
        {
                ret += (c[k] / (x + k));
        }

	/* -(x + a) */
        ret *= gexp(-(x + a)) * gpow(x + a, x + 0.5);

        return (ret / x);
}

