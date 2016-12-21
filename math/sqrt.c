#include "math.h"

double mysqrt(double x)
{

        /* babylonian method */
        double y; 
        int i;

        if ( x < 0)
                return -MYNAN;

        y = x;

        for(i=0; i < ((x / y) / 2) || i < 10 ; i++)
        {
                y = (( y + x / y ) / 2);
        }

        return y;
}


