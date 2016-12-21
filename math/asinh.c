#include "math.h"

double myasin(double x)
{
        int i = 0;
        int n = 3;

        double ratio = 0.5;
        double y;
        double z = 0;

        if ( x == 1.)
                return PI/2;
        else if ( x == -1.)
                return -PI/2;
        else if ( x > 1. || x < -1. )
                return MYNAN;

        y = x;

        while ( 1 )
        {
                y += ratio * (mypow(x, n) / n);
                n += 2;
                i += 1;
                ratio *= (1.0 + 2.0 * i) / (2.0 + 2.0 * i);
                if (y == z)
                        break;
                z = y;
        }

        return y;
}

