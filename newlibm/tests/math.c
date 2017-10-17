#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
double mysin(double);
int main(int argc, char *argv[])
{
        double x;

        if ( argc > 1 )
                x = strtod(argv[1], 0);
        else
                x = 19;

	printf("sin(123) solution is -0.4599034906895912512924357152932318108085806073810425809277\n");
	printf("sin(987.234234) solution is 0.6991019671507811957162690088283454921684870494514649920197948454594776556950092560712278850735646365\n");
        printf("sin(%lf) =     %19.25lf\n", x, sin(x));
	printf("floor(%lf) =     %19.19lf\n", x, floor(x));
	printf("mysin() =   %19.25lf  \n", mysin(x));
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
	printf("DBL_DIG %d\n", DBL_DIG);
	printf("DBL_EPSILON %19.19lf\n", DBL_EPSILON);
        return 0;
}

