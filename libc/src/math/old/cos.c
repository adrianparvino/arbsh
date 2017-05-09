#include <gmath.h>

double gcos(double x)
{
        size_t i = 0;
        size_t j = 0;
        int toggle = 1;
        double product = 1.0;
        double sum = 0;
	double last = 0;

	x = _arg_reduction(x);

        for (i = 0; i < 10; i++)
        {
                product = 1.0; 
                for (j = (2*i) ; j > 0 ; j--) 
                        product *= x / j; 

                sum += product * toggle; 

		if (_check_tolerance(last, sum))
                        break;

		last = sum;

        	toggle = -toggle;
        }

        return sum;
}


