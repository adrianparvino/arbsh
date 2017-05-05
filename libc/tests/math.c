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

        printf("libc sin =        %19.19f \n", sin(x)); 
        printf("  gsin =         %19.19f \n\n", gsin(x)); 
	printf("   sr func sin =        %19.19f \n\n", series_func_driver(x, 2)); 
        printf("libc cos =        %19.19f \n", cos(x)); 
        printf("   gcos =        %19.19f \n\n", gcos(x)); 
	printf("   sr func cos =        %19.19f \n\n", series_func_driver(x, 0)); 

        printf("libc tan =        %19.19f \n", tan(x)); 
        printf("  gtan =         %19.19f \n\n", gtan(x)); 
        printf("libc exp =        %19.19f \n", exp(x)); 
        printf("  gexp  =        %19.19f \n\n", gexp(x)); 
        printf("libc sinh =       %19.19f \n", sinh(x)); 
	printf("   sr func sinh =        %19.19f \n\n", series_func_driver(x, 3)); 
        printf("  gsinh =        %19.19f \n\n", gsinh(x)); 
        printf("libc cosh =       %19.19f \n", cosh(x)); 
        printf("  gcosh =        %19.19f \n\n", gcosh(x)); 
	printf("   sr func cosh =        %19.19f \n\n", series_func_driver(x, 1)); 
        //printf("libc tanh =       %19.19f \n", tanh(x)); 
        //printf("  gtanh =        %19.19f \n\n", gtanh(x)); 
	printf("libc log =       %19.19f \n", log(x));
        printf("  glog =        %19.19f \n\n", glog(x));
	
	printf("libc exp =       %19.19f \n", exp(x));
        printf("  gexp =        %19.19f \n\n", gexp(x));

        return 0;
}

