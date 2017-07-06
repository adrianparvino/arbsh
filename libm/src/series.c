#include <math.h>

/*
	Series function. 
	CM Graff, 2017

	Greater N achieves greater precision. This forumla has a range
	of -inf to inf. The formula calculates its aproximations using
	a cartesian product nested within a summation:

	  N       0
	____    _____
	\       |   |
	 >      |   | p(x/j)
	/___    |   |

        i = 0   j=(2*i)?+1

	The nested cartesian product converges onto zero and then imparts
	its aproximation to the outer summation which accumulates its
	results.

*/
double sin(double x)
{ 
	return series_func(x, 1, 1, 0);/* sin */ 
} 

double asin(double x)
{ 
	return aseries_func(x, 0);
} 

double sinh(double x)
{ 
	return series_func(x, 1, 0, 0);/* sinh */
} 

double cos(double x)
{ 
	return series_func(x, 0, 1, 0);
} 

double acos(double x)
{
	return aseries_func(x, 1);
}

double cosh(double x)
{
	return series_func(x, 0, 0, 0);/* cosh */
} 

double series_func_driver(double x, int selector)
{ 
        double sum = 0;

	if ( selector == 0 || selector == 2)
        	x = _arg_reduction(x);
	if ( selector == 0 ) 
		sum = series_func(x, 0, 1, 0);/* cos */ 
	if ( selector == 1 )
		sum = series_func(x, 0, 0, 0);/* cosh */
	if ( selector == 2 ) 
		sum = series_func(x, 1, 1, 0);/* sin */ 
	if ( selector == 3 )
		sum = series_func(x, 1, 0, 0);/* sinh */
	if ( selector == 4 )
		sum = series_func(x, 0, 0, 1);/* exp  >> 1*/ 
        return sum;
} 

double series_func(double x, int one, int toggler, int exp)
{
        size_t i = 0;
        size_t j = 0;
        double product = 1.0;
        double sum = 0;
        double last = 0;
	int toggle = 1;

        for (i = 0; i < 1000; i++)
        {
               	for (j = (2*i) + one, product = 1.0; j > 0 ; j--) 
                	product *= x / j;

               	sum += product * toggle;

		if ( toggler != 0 )
			toggle = -toggle; 

                if (_check_tolerance(last, sum))
                        break;

                last = sum; 
        }

	if ( exp )
		sum *=2;

        return sum;
}

double aseries_func(double x, int selector)
{
        int i = 0;
        int n = 3;

        double ratio = 0.5;
        double y;
        double z = 0;

        if ( x == 1.)
                return PI/2;
        else if ( x == -1.)
                return -PI/2;
        else if ( x > 1. || x < -1. )
                return MYNAN;

        y = x;

        while ( 1 )
        {
                y += ratio * (pow(x, n) / n);
                n += 2;
                i += 1;
                ratio *= (1.0 + 2.0 * i) / (2.0 + 2.0 * i);
                if (y == z)
                        break;
                z = y;
        }

	if ( selector == 0 ) /* asin */
        	{};
	if ( selector == 1 ) /* acos */
		return y = (PI / 2) - y;

	return y;

}

