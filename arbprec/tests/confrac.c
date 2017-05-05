#include <stdio.h>  
#include <math.h>   
#include <stdlib.h>


#define PI 3.14159265358979323846264

double trigfunc(int, double); 
double mysin(double);
double mycos(double);
double mytan(double);
double myexp(double);
double mysinh(double);
double mycosh(double);
double mytanh(double);
double mylog(double);
double mysqrt(double);

int main(int argc, char *argv[])
{
	double x; 
	
	if ( argc > 1 ) 
		x = strtod(argv[1], 0);
	else
		x = 19; 

	printf("libc sin =        %19.19f \n",sin(x)); 
	printf(" trigfunc sin =   %19.19f \n",trigfunc(1, x));
	printf("  mysin =         %19.19f \n\n",mysin(x));

	printf("libc cos =        %19.19f \n",cos(x));
	printf(" trigfunc cos =   %19.19f \n",trigfunc(2, x));
	printf("   mycos =        %19.19f \n\n",mycos(x));

	printf("libc tan =        %19.19f \n",tan(x));
	printf(" trigfunc tan  =  %19.19f \n",trigfunc(3, x));
	printf("  mytan =         %19.19f \n\n", mytan(x));

	printf("libc exp =        %19.19f \n", exp(x));
	printf(" trigfunc exp  =  %19.19f \n",trigfunc(5, x));
	printf("  myexp  =        %19.19f \n\n", myexp(x));
	
	printf("libc log =       %19.19f \n",log(x));
	printf(" trigfunc log =  %19.19f \n",trigfunc(4, x));
        printf("  mylog =        %19.19f \n\n", mylog(x));

	printf("libc sinh =       %19.19f \n",sinh(x));
	printf(" trigfunc sinh =  %19.19f \n",trigfunc(6, x));
	printf("  mysinh =        %19.19f \n\n", mysinh(x));

	printf("libc cosh =       %19.19f \n",cosh(x));
	printf(" trigfunc cosh =  %19.19f \n",trigfunc(7, x));
	printf("  mycosh =        %19.19f \n\n", mycosh(x));

	printf("libc tanh =       %19.19f \n",tanh(x));
	printf(" trigfunc tanh =  %19.19f \n",trigfunc(8, x));
	printf("  mytanh =        %19.19f \n\n", mytanh(x));
	
	printf("libc sqrt =       %19.19f \n",sqrt(x));
        printf("  mysqrt =        %19.19f \n\n", mysqrt(x));
 
	return 0;
} 


double trigfunc(int p, double x)
{
	int i = x + 30 / 4;
	double r = 0;
	double s = 0;
	double y = 0; 
	double Z = (x-1)/(x+1);
 

        
	i = 300;


	if (p <= 3)
	{
		r = - x * x;    /*  trig */
	}
	else
	{    
		r = x * x;      /* hyperbolic */
	} 
	
	s = 4 * i + 2;

	if ( p < 4 || p > 4 )
		for (; i > 0; i--) 
			s = 4 * i - 2 + r/s; 

	
	for (; p == 4 && i > 0; i--) 
		s = (2*i -1) - i*i*(Z*Z)/s;
		
	

	switch (p % 5)
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
			break;
	}
	return y;
}

double mysin(double x)
{
        double s = 1, y;
	int i; 
        double last = 0;
	double r = x * x;

	i =  x + 300; 

        for (; i > 0; i--)
        { 
		s = (((4 * i) - 2) - (r/s)); 
        } 

        /* (2xs) / (s^2 - x^2) */
	y = ((2 * x) * s)/((s * s) + r); 

        return y;

}
double mycos(double x)
{

        double s = 1, y; 
	int i = 30;
	double r = x * x;

	i = 30;

        if ( x < 0. )
                i = -x + 30 / 4; 

        for (; i > 0; i--)
        { 
		s = (((4 * i) - 2) - (r/s));
        } 
	/* s^2 - x^2 / s^2 - x^2 */
	y = ((s * s) - r)/((s * s) + r); 
    
        return y;
}
double mytan(double x)
{

        double s = 1, y;
        int i;
	double r = x * x;

	i = 30; 
       

        for (; i > 0; i--)
        { 
		s = ((4 * i - 2) - (r/s)); 
        } 
	y = 2 * x * s/(s * s - r); 
	
        return y;
}


double myexp(double x)
{ 
        double s = 1, y;
        int i = 30000000;
	double last = 0;
	double r = x * x;

	i = 30; 

        for (; i>0; i--)
        { 
		s = (((4 * i) - 2) + (r/s));
                if ( last == s )
                        break;
        }
        y = (s + x)/(s - x);

        return y;
}

double mysinh(double x)
{
        int i = 30;
        double s = 0, y;
	double r = x * x;


        for (; i > 0; i--)
        { 
		s = (((4 * i) - 2) + (r/s)); 
        } 
        

	y = 2 * x * s/(s * s - r); 

	return y;
}

double mycosh(double x)
{
        int i = 30;
        double s = 1, y;
	double r = x * x;
	
        for (; i > 0; i--)
        {
                s = (((4 * i) - 2) + (r/s)); 
        } 
        y = (s * s + r)/(s * s - r); 
        return y;
}

double mytanh(double x)
{
        int i;
        double s = 1, y;
	double r = x * x;

        i =  30; 

        for (; i > 0; i--)
        { 
		s = (((4 * i) - 2) + (r/s)); 
        } 
        y = 2 * x * s/(s * s + r);   /* tan, tanh */ 
        
        return y;
}

double mylog(double x)
{ 
	int i;
	double s = 1;
	double X = x-1;
	double Y = x+1;
	double Z = X / Y; 

	i = 300;

	for (i ; i>0; i--)
	{ 
		s = (2*i -1) - i*i*(Z*Z)/s; 
		//printf("%lf\n", s);
	} 

	return 2*Z/s;
	
}


double mysqrt(double x)
{ 
	int i;
	double s = 1;
	double X = x-1;
	double Y = x+1;
	double Z = X / Y; 

	i = x + 3;

	for (i ; i>0; i--)
	{ 
		s = (2*i -1) - i*i*(Z*Z)/s; 
		//printf("%lf\n", s);
	} 

	return 2*Z/s;
	
}





