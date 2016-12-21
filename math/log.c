#include "math.h"

double mylog(double x)
{
        int n = 1;
        double y = 0;
        double z = 0;

        /*
                Taylor series 
                ln(x) = 2((x-1/x+1) + 1/3(x-1/x+1)^3 + 1/5(x-1/x+1) + ... ) 
        */

        if (x <= 0 )
                return MYNAN; 

	
	
        while ( 1 && n < 10000)
        {
        	y += (mypow((x - 1)/(x + 1), n) / n ); 

                n+=2;
	
                if ( y == z )
                        break;
                z = y;
		
        }

	return  y * 2; 

}


