#include <math.h>
#include <stdint.h>
#include <limits.h>
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
#define PI 3.14159265358979323846
#define size_t uint32_t
double series_func(double x, int one, int toggler, int exp);
double series_func_driver(double x, int selector);
double mysin(double x);
double mysin(double x)
{ 
	//return series_func(x, 1, 1, 0);/* sin */ 
	return series_func_driver(x, 2);
} 
/*
double asin(double x)
{ 
	return aseries_func(x, 0);
} 

double sinh(double x)
{ 
	return series_func(x, 1, 0, 0);
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
	return series_func(x, 0, 0, 0);
} 
*/
double series_func_driver(double x, int selector)
{ 
        double sum = 0;
	double y[2];
	int n = 0;
	if ( selector == 0 || selector == 2)
	{
        	//x = _arg_reduction(x);
	        y[0] = x;
	        y[1] = x; 
	        n = ____rem_pio2(x, y);
		switch (n&3) {
		
		        case 0: return series_func(y[0], 1, 1, 0); // ____sin(y[0], y[1], 1);
		        case 1: return series_func(y[0], 0, 1, 0); // ____cos(y[0], y[1]);
		        case 2: return - series_func(y[0], 1, 1, 0); //-____sin(y[0], y[1], 1);
		        default:
	                return -series_func(y[0], 0, 1, 0);//-____cos(y[0], y[1]);
	        }
	}
        //printf("mysin() =   %19.19lf  \n", mysin(y[0]));

	if ( selector == 0 ) 
		sum = series_func(x, 0, 1, 0);/* cos */ 
	if ( selector == 1 )
		sum = series_func(x, 0, 0, 0);/* cosh */
	if ( selector == 2 ) 
		sum = series_func(y[0], 1, 1, 0);/* sin */ 
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
	size_t inner = 0;
	size_t outer = 0;

        for (i = 0; i < SIZE_MAX; i++)
        {
               	for (j = (2*i) + one, product = 1.0; j > 0 ; j--) 
		{
			//printf("outer %zu\n", outer++);
                	product *= x / j;
		}
		//printf("inner %zu\n", inner++);
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
