#include "math.h"

double mycos(double x)
{
        int i;
        int j;
        int toggle = 1;
        double product;
        double last;
        double sum;

        sum = 0.0;
        last = 0;

        while ( x >= (2*PI))
                x -= (2*PI);
        while ( x < 0 )
                x += (2*PI);


        for (i = 0; 1 ; i++)
        {
                product = 1.0;

                for (j = (2*i) ; j > 0 ; j--)
                {
                        product *= x / j;
                }
                sum += product * toggle;

                if ( sum == last )
                        break;
                last = sum;

                toggle = -toggle;
        }

        return sum;
}


