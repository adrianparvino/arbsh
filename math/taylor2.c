#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846264
#define EULER 2.718281828459045
#define MYNAN -(0./0.)

double taylor(double); 
double myacos(double);
double myasin(double);
double myasinh(double); 


int main(int argc, char *argv[])
{
        double x = strtod(argv[1], 0);
        double z = 0;

        z = acos(x);
        printf("libm acos %lf\n", z);
        z = myacos(x);
        printf("mycos %lf\n", z);

        z = asin(x);
        printf("libm asin %lf\n", z);
        z = myasin(x);
        printf("myasin %lf\n", z); 
	
	z = asinh(x);
        printf("libm asinh %lf\n", z);
        z = myasinh(x);
        printf("myasinh %lf\n", z);
        return 0; 
}


double myasin(double x)
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

        return y;
}



double myacos(double x)
{
        /* identity: acos(x) = (PI / 2) + asin(-x) */
        int i = 0;
        int n = 3;

        double ratio = 0.5;
        double y;
        double z = 0;

        if ( x == 1.0)
                return 0.00000000;
        else if ( x < -1.)
                return MYNAN;
        else if ( x >= 1. )
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


        return (PI / 2) - y;

}


double myasinh(double x)
{
        int i = 0;
        int n = 3;
	
	int sign = -1;
        double ratio = 0.5;
        double y;
        double z = 0;

        if ( x == 1.)
                return PI/2;
        else if ( x == -1.)
                return -PI/2; 

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
		sign = -sign;
        } 

        return y;
}


