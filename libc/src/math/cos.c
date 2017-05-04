#include <gmath.h>

double gcos(double x)
{
        int i;
        int j;
        int toggle = 1;
        double product;
        double last;
        double sum;

        sum = 0.0;
        last = 0;

	x = _arg_reduction(x);

        for (i = 0; i < 10; i++)
        {
                product = 1.0;

                for (j = (2*i) ; j > 0 ; j--)
                {
                        product *= x / j;
                }
                sum += product * toggle; 
        	toggle = -toggle;
        }

        return sum;
}


