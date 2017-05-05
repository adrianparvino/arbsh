#include <gmath.h>

/*
	Series function written by CM Graff, 2017

	Greater N achieves greater precision.

	  N       0 
	____    _____
	\       |   |
	 >      |   | p(x/j)
	/___    |   |

        i = 0   j=(2*i)?+1


	summation ...

		cartesian product ...  
*/

double series_func_driver(double x, int selector)
{ 
        double sum = 0;

	if ( selector == 0 || selector == 2)
        	x = _arg_reduction(x);
	if ( selector == 0 ) 
		sum = series_func(x, 0, 1);/* cos */ 
	if ( selector == 1 )
		sum = series_func(x, 0, 0);/* cosh */
	if ( selector == 2 ) 
		sum = series_func(x, 1, 1);/* sin */ 
	if ( selector == 3 )
		sum = series_func(x, 1, 0);/* sinh */ 
        return sum;
}


double series_func(double x, int one, int toggle)
{
        size_t i = 0;
        size_t j = 0;
        double product = 1.0;
        double sum = 0;
        double last = 0; 

        for (i = 0; i < 1000; i++)
        { 
                for (j = (2*i) + one, product = 1.0; j > 0 ; j--)
                        product *= x / j;

		if ( toggle != 0 )
		{
                	sum += product * toggle;
			toggle = -toggle;
		}
		else 
			sum += product;

                if (_check_tolerance(last, sum))
                        break;

                last = sum; 
        }

        return sum;
}

