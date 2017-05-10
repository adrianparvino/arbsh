#include <stdio.h>  
#include <math.h>   
#include <stdlib.h> 
#define PI 3.14159265358979323846264

double trigfunc(int, double);

int main(int argc, char *argv[])
{
	double x; 
	
	if ( argc > 1 ) 
		x = strtod(argv[1], 0);
	else
		x = 19; 

	printf("libc sin =        %19.19f \n", sin(x)); 
	printf(" trigfunc sin =   %19.19f \n", trigfunc(1, x)); 

	printf("libc cos =        %19.19f \n", cos(x));
	printf(" trigfunc cos =   %19.19f \n", trigfunc(2, x)); 

	printf("libc tan =        %19.19f \n", tan(x));
	printf(" trigfunc tan  =  %19.19f \n", trigfunc(3, x)); 

	printf("libc exp =        %19.19f \n", exp(x));
	printf(" trigfunc exp  =  %19.19f \n", trigfunc(6, x)); 
	
	printf("libc log =        %19.19f \n", log(x));
	printf(" trigfunc log =   %19.19f \n", trigfunc(4, x)); 

	printf("libc sinh =       %19.19f \n", sinh(x));
	printf(" trigfunc sinh =  %19.19f \n", trigfunc(7, x)); 
	
	printf("libc atanh =      %19.19f \n\n", atanh(x));
	printf(" trigfunc atanh = %19.19f \n\n", trigfunc(5, x));

	printf("libc cosh =       %19.19f \n", cosh(x));
	printf(" trigfunc cosh =  %19.19f \n", trigfunc(8, x)); 

	printf("libc tanh =       %19.19f \n", tanh(x));
	printf(" trigfunc tanh =  %19.19f \n", trigfunc(9, x)); 
	
	printf("libc sqrt =       %19.19f \n",sqrt(x)); 
 
	return 0;
} 


double trigfunc(int p, double x)
{
	size_t i = 300;
	double r = 0;
	double s = 0;
	double y = 0;
	double Z = (x-1)/(x+1);
	double ZZ= 0;

	if ( p == 5)
		Z=x; 
	Z = Z * Z;

	if (p <= 3)
		r = - x * x;    /* trig */
	else 
		r = x * x;      /* hyperbolic */
	
	s = 4 * i + 2;

	if ( p < 4 || p > 5 )	/* ! log */
		for (; i > 0; i--) 
			s = 4 * i - 2 + r/s;
	
	for (; (p == 4 || p == 5) && i > 0; i--) /* log */
		s = (2*i -1) - i*i*(ZZ)/s;

	switch (p % 6)
	{
		case 0 : 
			y = (s + x)/(s - x);		/* exp */
			break;
		case 1 : 
			y = 2 * x * s/(s * s - r);	/* sin, sinh */
			break;
		case 2 : 
			y = (s * s + r)/(s * s - r);	/* cos, cosh */
			break;
		case 3 : 
			y = 2 * x * s/(s * s + r);	/* tan, tanh */
			break; 
		case 4 :
			y = 2*Z/s;			/* log */
			break; 
		case 5 : 
			y = (2*Z/s) / 2;		/* atanh */
			break;
		case 6 :
			break;

		/*
			These all have identities relating to log
			so can likely be expressed using this series
			function

			asinh(x) = ln( x + [sqrt](x2 + 1) ) 
			acosh(x) = ln( x [sqrt](x2 - 1) ) 
			atanh(x) = 1/2 ln( (1+x)/(1-x) ) 
			acsch(x) = ln( (1+[sqrt](1+x2) )/x ) 
			asech(x) = ln( (1[sqrt](1-x2) )/x ) 
			acoth(x) = 1/2 ln( (x+1)/(x-1) ) 


			Conversely, these functions all bear a
			relations ship to exp()

			sinh(x) = ( e(x) - e(-x) )/2 
			csch(x) = 1/sinh(x) = 2/( e(x) - e(-x) ) 
			cosh(x) = ( e(x) + e(-x) )/2 
			sech(x) = 1/cosh(x) = 2/( e(x) + e(-x) ) 
			tanh(x) = sinh(x)/cosh(x) = ( e(x) - e(-x) )/( e(x) + e(-x) ) 
			coth(x) = 1/tanh(x) = ( e(x) + e(-x))/( e(x) - e(-x) ) 
		*/
	
	}
	return y;
}

