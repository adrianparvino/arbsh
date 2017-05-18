#include <gmath.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        double x;

        if ( argc > 1 )
                x = strtod(argv[1], 0);
        else
                x = 19;

        printf("libc sin =     %19.19f\n", sin(x)); 
        printf("gsin =         %19.19f\n", gsin(x)); 
	printf("taylor sin =   %19.19f\n", series_func_driver(x, 2)); 
	printf("confrac sin = %19.19f\n", trigfunc(1, x)); 
	printf("\n\n"); 
        printf("libc cos =     %19.19f\n", cos(x)); 
        printf("gcos =         %19.19f\n", gcos(x)); 
	printf("taylor cos =   %19.19f\n", series_func_driver(x, 0)); 
	printf("confrac cos = %19.19f\n", trigfunc(2, x));
	printf("\n\n");
        printf("libc tan =     %19.19f\n", tan(x)); 
	printf("confrac tan  = %19.19f\n", trigfunc(3, x)); 
	printf("\n\n");
        printf("libc sinh =    %19.19f\n", sinh(x)); 
	printf("taylor sinh =  %19.19f\n", series_func_driver(x, 3)); 
        printf("gsinh =        %19.19f\n", gsinh(x)); 
	printf("confrac sinh = %19.19f\n", trigfunc(7, x));
	printf("\n\n");
        printf("libc cosh =    %19.19f\n", cosh(x)); 
        printf("gcosh =        %19.19f\n", gcosh(x)); 
	printf("taylor cosh =  %19.19f\n", series_func_driver(x, 1)); 
	printf("confrac cosh = %19.19f\n", trigfunc(8, x));
	printf("\n\n");
	printf("libc log =     %19.19f\n", log(x));
        printf("glog =         %19.19f\n", glog(x));
	printf("confrac log =  %19.19f\n", trigfunc(4, x));
	printf("\n\n");
	printf("libc exp =     %19.19f\n", exp(x));
        printf("gexp =         %19.19f\n", gexp(x));
	printf("taylor exp =   %19.19f\n", series_func_driver(x, 4));
	printf("confrac exp  = %19.19f\n", trigfunc(6, x));
	printf("\n\n");
	
	printf("libc acos =    %19.19f\n", acos(x));
        printf("gacos =        %19.19f\n", gacos(x));
	printf("taylor gacos = %19.19f\n", aseries_func(x, 1));
	printf("\n\n");
	printf("libc asin =    %19.19f\n", asin(x));
        printf("gasin =        %19.19f\n", gasin(x));
	printf("taylor gasin = %19.19f\n", aseries_func(x, 0));
	printf("\n\n");
	printf("libc tanh =    %19.19f\n", tanh(x));
        printf("confrac tanh = %19.19f\n", trigfunc(9, x));
	printf("confrac atanh =%19.19f\n", trigfunc(5, x));
	printf("\n\n");
        return 0;
}

