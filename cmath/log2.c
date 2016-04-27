#include "math.h"


double mylog2(double x)
{
        int n = 1;
        double y = 0;
        double z = 0; 


        if (x <= 0 )
                return MYNAN;

        while ( 1 && n < 100000)
        {
                y += (mypow((x - 1)/(x + 1), n) / n );
                n+=2;
                if ( y == z )
                        break;
                z = y;
        }

        return  y;

}


