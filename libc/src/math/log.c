#include "math.h"

double glog(double x)
{
        int n = 1;
        double y = 0;
        double z = 0;
	double Z = (x-1)/(x+1);

        /*
                Log.c using the Taylor series:
                ln(x) = 2((x-1/x+1) + 1/3(x-1/x+1)^3 + 1/5(x-1/x+1) + ... ) 
        */

        if (x <= 0 )
                return MYNAN;
	
        while (n < 100)
        {
        	y += (gpow(Z, n) / n ); 
                n+=2; 
                if ( y == z )
                        break;
                z = y;
        }

	return  y * 2;
}


