#include "math.h"

double mygamma(double x)
{ 
        int a = 12;
        int k;
        double c[a];
        double fac = 1.0;
        double ret;
	

        ret = mysqrt(2.0 * PI);

        for( k = 1; k < a ; k++)
        {
                c[k] = ((myexp(a - k) * mypow(a - k, k - 0.5)) / fac); 
                fac *= -k;
        }

        for( k = 1; k < a ; k++)
        {
                ret += (c[k] / (x + k));
        }

	/* -(x + a) */
        ret *= myexp(-(x + a)) * mypow(x + a, x + 0.5);
	

        return (ret / x);
}

