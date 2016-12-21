#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846264
#define EULER 2.718281828459045
#define MYNAN -(0./0.)


double taylor(double);

double mylog(double);
double myatan(double); 


int main(int argc, char *argv[])
{
        double x = strtod(argv[1], 0);
        double z = 0;

        z = log(x);
        printf("libc cosh %lf\n", z);
        z = mylog(x);
        printf("mycosh %lf\n", z);

        z = atan(x);
        printf("libc sinh %lf\n", z);
        z = myatan(x);
        printf("mysinh %lf\n", z);

        /*
        z = exp(x);
        printf("libc exp %lf\n", z);
        z = myexp(x);
        printf("myexp %lf\n", z);
        */
        return 0;


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

double myatan(double x)
{
        /* taylor series based atan(x) aproximation */
        int j = 3;
        double z = 0;
        int sign = -1;
        double y = x;

        /* x = x - x^3/3 + x^3/3 - x^3/3 + ...  */
        while (x < 1.0 && x > -1.0 &&  1)
        {
                y += (pow(x, j)/(j) * sign);
                if (z == y)
                        break;
                z = y;
                j += 2;
                sign = -sign;

        }
        /* x = pi/2 .... if >= 1. */
        if (x >= 1. )
        {
                y = (PI/2);
        }
        /* x = - pi/2 .... if <= -1. */
        else if (x <= -1. )
        {
                y = -(PI/2);
        }
        /* ... 1/x + 1/(3*(x^3)) - 1/(5*x^5) + 1/(7*x^7) - ...  */
        for (j = 1; (x >= 1. || x <= -1.) && 1;)
        {
                y += (1/ (j *(pow(x, j)))) * sign;
                if (z == y)
                        break;
                z = y;
                j += 2;
                sign = -sign;
        }

        return  y;

}

