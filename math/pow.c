#include "math.h"

double mypow(double x, double n)
{

        double y = 1;

        /* negative */
        if (n < 0)
                y = 1.0 / mypow(x, -n);
        /* whole number */
        else if (n == (long long)n)
        {
                while (n--)
                      y *= x;
        }
        /* fractional */
        else
                y = myexp(n * mylog(x)); 

        return y;
}


