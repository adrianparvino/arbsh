#include "math.h"

double myatanh(double x)
{
        /* taylor series based atanh(x) aproximation */
        int j = 3;
        double z = 0; 
        double y = 0;

        /* x = x + x^3/3 + x^3/3 + x^3/3 + ...  */
        while (x < 1.0 && x > -1.0 &&  1)
        {
                y += (mypow(x, j)/(j));
                if (z == y)
                        break;
                z = y;
                j += 2;
        }
        /* x = pi/2 .... if >= 1. */
        if (x >= 1. )
        {
                y = (PI/2);
        }
        /* x = - pi/2 .... if <= -1. */
        else if (x <= -1. )
        {
                y = -(PI/2);
        }
        /* ... 1/x + 1/(3*(x^3)) + 1/(5*x^5) + 1/(7*x^7) + ...  */
        for (j = 1; (x >= 1. || x <= -1.) && 1;)
        {
                y += (1/ (j *(mypow(x, j))));
                if (z == y)
                        break;
                z = y;
                j += 2;

        }

        return  y;

}

