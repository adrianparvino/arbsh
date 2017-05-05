#include <gmath.h>

double gsin(double x)
{
        int i;
        int j;
        int toggle = 1;
        double product;
        double last = 0;
        double sum = 0;
	double rl = 0;

	x = _arg_reduction(x);

        for (i = 0; i < 10 ; i++)
        {
                product = 1.0;
                for (j = (2*i) + 1 ; j > 0 ; j--) 
                        product *= (x / j);
                sum += product * toggle;
                toggle = -toggle; 
        }

        return sum;
}


