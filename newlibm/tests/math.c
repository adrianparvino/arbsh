#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double mysin(double);
int main(int argc, char *argv[])
{
        double x;

        if ( argc > 1 )
                x = strtod(argv[1], 0);
        else
                x = 19;

        printf("sin(%lf) =     %19.19lf\n", x, sin(x));
	printf("floor(%lf) =     %19.19lf\n", x, floor(x));
	printf("mysin() =   %19.19lf  \n", mysin(x));
        printf("cos =     %19.19f\n", cos(x));
	/*
        printf("sinh =    %19.19f\n", sinh(x));
        printf("cosh =    %19.19f\n", cosh(x));
	printf("log =     %19.19f\n", log(x));
	printf("exp =     %19.19f\n", exp(x));
	printf("acos =    %19.19f\n", acos(x));
	printf("asin =    %19.19f\n", asin(x));
	printf("tanh =    %19.19f\n", tanh(x));
	printf("tan =     %19.19f\n", tan(x));
	printf("atan =    %19.19f\n", atan(x));
	*/

        return 0;
}

