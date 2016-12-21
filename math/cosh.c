#include "math.h"

double mycosh(double x)
{
        int i;
        int j; 
        double product;
        double last;
        double sum;

        sum = 0.0;
        last = 0; 

        for (i = 0; 1 ; i++)
        {
                product = 1.0;

                for (j = (2*i) ; j > 0 ; j--)
                {
                        product *= x / j;
                }
                sum += product;

                if ( sum == last )
                        break;
                last = sum;

                
        }

        return sum;
}


