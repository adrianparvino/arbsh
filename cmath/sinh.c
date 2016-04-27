#include "math.h"
           


double mysinh(double x)
{
        long i;
        long j; 
        double product;
        double last = 0;
        double sum = 0; 

        for (i = 0; i < 10000 ; i++)
        {
                product = 1.0;
                for (j = (2*i) + 1 ; j > 0 ; j--)
                {
                        product *= (x / j);
                }
                sum += product; 
                if ( sum == last )
                        break;
                last = sum;
        }

        return sum;
}


