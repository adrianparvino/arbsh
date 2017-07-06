#include <math.h>

double log(double x)
{
        size_t n = 1;
        double y = 0;
        double z = 0;
	double Z = (x-1)/(x+1);

        /*
                Log.c using the Taylor series:
                ln(x) = 2((x-1/x+1)^1 + 1/3(x-1/x+1)^3 + 1/5(x-1/x+1)^5 + ... ) 
        */

        if (x <= 0 )
                return MYNAN;
	
        while (1)
        {
        	y += (pow(Z, n) / n);
                n+=2; 
                if (_check_tolerance(z, y))
                        break;
                z = y;
        }

	return  y * 2;
}


