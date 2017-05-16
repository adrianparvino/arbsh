#include <gmath.h>

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

	ZZ = Z * Z;

	if (p <= 3)
		r = - x * x;    /* trig */
	else 
		r = x * x;      /* hyperbolic */
	
	s = 4 * i + 2;

	if ( p < 4 || p > 5 )	/* ! log */
		for (; i > 0; i--) 
			s = 4 * i - 2 + r/s;
	
	for (; (p == 4 || p == 5) && i > 0; i--) /* log */
	{
		s = (2*i -1) - i*i*(ZZ)/s;
		printf("%lf\n", s);
	}

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
	}
	return y;
}

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


