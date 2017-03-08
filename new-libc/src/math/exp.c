#include "math.h"

double myexp(double x)
{
        int i;
        int n = 0;
        double y = 0;
        double d = 0;
        double z = 0;

        if (x == 1.0) {
                y = EULER;
        } else if (x < 0) {
                y = 1.0 / myexp(-x);
        } else {
                n = 2;
                y = 1.0 + x;
                while ( 1 )
                {
                        d = x;
                        for (i = 2; i <= n; i++)
                        {
                                d *= x / i; 
                        }
                        y += d;
                        n++;
                        if ( y == z )
                                break;
                        z = y;
                }
        }
        return y;
}


