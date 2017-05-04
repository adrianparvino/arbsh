#include <gmath.h>

double gsinh(double x)
{
        long i;
        long j; 
        double product;
        double last = 0;
        double sum = 0; 

	x = _arg_reduction(x);

        for (i = 0; i < 10 ; i++)
        {
                product = 1.0;
                for (j = (2*i) + 1 ; j > 0 ; j--)
                {
                        product *= (x / j);
                }
                sum += product; 
        }

        return sum;
}


