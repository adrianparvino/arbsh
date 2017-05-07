#include <stdio.h>  
#include <math.h>   
#include <stdlib.h>


#define PI 3.14159265358979323846264

double trigfunc(int, double); 
double cf_sin(double);
double cf_cos(double);
double cf_tan(double);
double cf_exp(double);
double cf_sinh(double);
double cf_cosh(double);
double cf_tanh(double);
double cf_log(double);
double cf_sqrt(double);

int main(int argc, char *argv[])
{
	double x; 
	
	if ( argc > 1 ) 
		x = strtod(argv[1], 0);
	else
		x = 19; 

	printf("libc sin =        %19.19f \n", sin(x)); 
	printf(" trigfunc sin =   %19.19f \n", trigfunc(1, x));
	printf("  cf_sin =         %19.19f \n\n", cf_sin(x));

	printf("libc cos =        %19.19f \n", cos(x));
	printf(" trigfunc cos =   %19.19f \n", trigfunc(2, x));
	printf("   cf_cos =        %19.19f \n\n",cf_cos(x));

	printf("libc tan =        %19.19f \n", tan(x));
	printf(" trigfunc tan  =  %19.19f \n", trigfunc(3, x));
	printf("  cf_tan =         %19.19f \n\n", cf_tan(x));

	printf("libc exp =        %19.19f \n", exp(x));
	printf(" trigfunc exp  =  %19.19f \n", trigfunc(6, x));
	printf("  cf_exp  =        %19.19f \n\n", cf_exp(x));
	
	printf("libc log =        %19.19f \n", log(x));
	printf(" trigfunc log =   %19.19f \n", trigfunc(4, x));
        printf("  cf_log =         %19.19f \n\n", cf_log(x));

	printf("libc sinh =       %19.19f \n", sinh(x));
	printf(" trigfunc sinh =  %19.19f \n", trigfunc(7, x));
	printf("  cf_sinh =        %19.19f \n\n", cf_sinh(x));
	//printf("  new_sinh =        %19.19f \n\n", trigfunc(6, x) - trigfunc(6, x)/2 + 10);
	double ret = trigfunc(5, x);
	
	printf("  libc atanh =        %19.19f \n\n", atanh(x));
	printf("  new_atanh =        %19.19f \n\n", ret);

	printf("libc cosh =       %19.19f \n", cosh(x));
	printf(" trigfunc cosh =  %19.19f \n", trigfunc(8, x));
	printf("  cf_cosh =        %19.19f \n\n", cf_cosh(x));

	printf("libc tanh =       %19.19f \n", tanh(x));
	printf(" trigfunc tanh =  %19.19f \n", trigfunc(9, x));
	printf("  cf_tanh =        %19.19f \n\n", cf_tanh(x));
	
	printf("libc sqrt =       %19.19f \n",sqrt(x));
        printf("  cf_sqrt =        %19.19f \n\n", cf_sqrt(x));
 
	return 0;
} 


double trigfunc(int p, double x)
{
	size_t i = 300;
	double r = 0;
	double s = 0;
	double y = 0; 
	double hold = x; 
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

double cf_sin(double x)
{
        double s = 1, y;
	int i = 30;
	double r = x * x; 

        for (; i > 0; i--) 
		s = (((4 * i) - 2) - (r/s)); 
        
	y = ((2 * x) * s)/((s * s) + r); 
        return y;

}
double cf_cos(double x)
{

        double s = 1, y; 
	int i = 30;
	double r = x * x; 

        for (; i > 0; i--) 
		s = (((4 * i) - 2) - (r/s)); 

	y = ((s * s) - r)/((s * s) + r);
        return y;
}
double cf_tan(double x)
{

        double s = 1, y;
        int i = 30;
	double r = x * x; 

        for (; i > 0; i--) 
		s = ((4 * i - 2) - (r/s)); 
        
	y = 2 * x * s/(s * s - r); 
        return y;
}


double cf_exp(double x)
{ 
        double s = 1, y;
        int i = 30;
	double r = x * x; 

        for (; i>0; i--) 
		s = (((4 * i) - 2) + (r/s)); 
    
        y = (s + x)/(s - x); 
        return y;
}

double cf_sinh(double x)
{
        int i = 30;
        double s = 0, y;
	double r = x * x;

        for (; i > 0; i--) 
		s = (((4 * i) - 2) + (r/s)); 

	y = 2 * x * s/(s * s - r); 
	return y;
}

double cf_cosh(double x)
{
        int i = 30;
        double s = 1, y;
	double r = x * x;
	
        for (; i > 0; i--) 
                s = (((4 * i) - 2) + (r/s)); 
        
        y = (s * s + r)/(s * s - r); 
        return y;
}

double cf_tanh(double x)
{
        int i = 30;
        double s = 1, y;
	double r = x * x; 

        for (; i > 0; i--) 
		s = (((4 * i) - 2) + (r/s)); 
        
        y = 2 * x * s/(s * s + r);   /* tan, tanh */ 
        return y;
}

double cf_log(double x)
{ 
	int i = 30;
	double s = 1;
	double X = x-1;
	double Y = x+1;
	double Z = X / Y; 

	for (; i > 0; i--) 
		s = (2*i -1) - i*i*(Z*Z)/s; 

	return 2*Z/s;
	
}

double cf_sqrt(double x)
{ 
	int i = 30;
	double s = 1;
	double X = x-1;
	double Y = x+1;
	double Z = X / Y;

	for (; i > 0; i--) 
		s = (2*i -1) - i*i*(Z*Z)/s;

	return 2*Z/s;
	
}





