#include <gmath.h>

double gsinh(double x)
{
        size_t i = 0;
        size_t j = 0;
	double product = 1.0;
        double last = 0;
        double sum = 0;


        for (i = 0; i < 10 ; i++)
        {
                product = 1.0;

                for (j = (2*i) + 1 ; j > 0 ; j--) 
                        product *= (x / j);
  
                sum += product; 
        }

        return sum;
}


