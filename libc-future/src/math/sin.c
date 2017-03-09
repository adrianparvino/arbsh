#include "math.h"
           


double mysin(double x)
{
        int i;
        int j;
        int toggle = 1;
        double product;
        double last = 0;
        double sum = 0;

        while ( x >= (2*PI))
                x -= (2*PI);

        while ( x < 0 )
                x += (2*PI);

        for (i = 0; i < 10000 ; i++)
        {
                product = 1.0;
                for (j = (2*i) + 1 ; j > 0 && product > EPS ; j--)
                {
                        product *= (x / j);
                }
                sum += product * toggle;
                toggle = -toggle;
                if ( sum == last )
                        break;
                last = sum;
        }

        return sum;
}


