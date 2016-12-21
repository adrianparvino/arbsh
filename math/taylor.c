#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846264
#define EULER 2.718281828459045
#define MYNAN -(0./0.)

double taylor(double); 

double mycos(double);
double mysin(double);
double mycosh(double);
double mysinh(double);

double myexp(double);


int main(int argc, char *argv[])
{
	double x = strtod(argv[1], 0);
	double z = 0;
	
	z = cos(x);
        printf("libx cos %lf\n", z);
	z = mycos(x); 
	printf("mycos %lf\n", z);

        z = sin(x);
	printf("sin %lf\n", z);
        z = mysin(x); 
        printf("mysin %lf\n", z);

        z = cosh(x);
        printf("libc cosh %lf\n", z);
        z = mycosh(x); 
        printf("mycosh %lf\n", z);

	z = sinh(x);
        printf("libc sinh %lf\n", z);
        z = mysinh(x);
        printf("mysinh %lf\n", z);

	z = exp(x);
        printf("libc exp %lf\n", z);
        z = myexp(x);
        printf("myexp %lf\n", z);

	return 0;
	
	
}


double mycos(double x)
{
        int i;
        int j;
        int sign = 1;
        double d;
        double z;
        double y;

        y = 0.0;
        z = 0;

        while ( x >= (2*PI))
                x -= (2*PI);
        while ( x < 0 )
                x += (2*PI);


        for (i = 0; 1 ; i++)
        {
                d = 1.0;

                for (j = (2*i) ; j > 0 ; j--)
                {
                        d *= x / j;
                }
                y += d * sign;

                if ( y == z )
                        break;
                z = y;

                sign = -sign;
        }

        return y;
}

double mysin(double x)
{
        int i;
        int j;
        int sign = 1;
        double d;
        double z = 0;
        double y = 0;

        while ( x >= (2*PI))
                x -= (2*PI);

        while ( x < 0 )
                x += (2*PI);

        for (i = 0; 1; i++)
        {
                d = 1.0;
                for (j = (2*i) + 1 ; j > 0; j--)
                {
                        d *= (x / j);
                }
                y += d * sign;
                sign = -sign;
                if ( y == z )
                        break;
                z = y;
        }

        return y;
}

double mysinh(double x)
{
        long i;
        long j;
        double d;
        double z = 0;
        double y = 0;

        for (i = 0; 1 ; i++)
        {
                d = 1.0;
                for (j = (2*i) + 1 ; j > 0 ; j--)
                {
                        d *= (x / j);
                }
                y += d;
                if ( y == z )
                        break;
                z = y;
        }

        return y;
}

double mycosh(double x)
{
        int i;
        int j;
        double d;
        double z;
        double y;

        y = 0.0;
        z = 0;

        for (i = 0; 1 ; i++)
        {
                d = 1.0;

                for (j = (2*i) ; j > 0 ; j--)
                {
                        d *= x / j;
                }
                y += d;

                if ( y == z )
                        break;
                z = y;


        }

        return y;
}



double myexp(double x)
{
        int i;
        int n = 0;
        double y = 0;
        double d = 0;
        double z = 0;


        if (x == 1.0) {
                y = EULER;
        } else if (x < 0) {
                y = 1.0 / myexp(-x);
        } else {
                n = 2;
                y = 1.0 + x;
                while ( 1 )
                {
                        d = x;
                        for (i = 2; i <= n; i++)
                        {
                                d *= x / i;
                        }
                        y += d;
                        n++;
                        if ( y == z )
                                break;
                        z = y;
                }
        }
        return y;
}

double mylog(double x)
{
        int n = 1;
        double y = 0;
        double z = 0;

        /*
                Taylor series 
                ln(x) = 2((x-1/x+1) + 1/3(x-1/x+1)^3 + 1/5(x-1/x+1) + ... ) 
        */

        if (x <= 0 )
                return MYNAN;



        while ( 1 && n < 10000)
        {
                y += (pow((x - 1)/(x + 1), n) / n );

                n+=2;

                if ( y == z )
                        break;
                z = y;

        }

        return  y * 2;

}

