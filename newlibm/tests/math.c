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
	printf("\n\n"); 
	/*
        printf("libc cos =     %19.19f\n", cos(x)); 
	printf("\n\n");
        printf("libc sinh =    %19.19f\n", sinh(x)); 
	printf("\n\n");
        printf("libc cosh =    %19.19f\n", cosh(x)); 
	printf("\n\n");
	printf("libc log =     %19.19f\n", log(x)); 
	printf("libc exp =     %19.19f\n", exp(x)); 
	printf("\n\n"); 
	printf("libc acos =    %19.19f\n", acos(x)); 
	printf("\n\n");
	printf("libc asin =    %19.19f\n", asin(x)); 
	printf("\n\n");
	//printf("libc tanh =    %19.19f\n", tanh(x));
	//printf("libc tan =     %19.19f\n", tan(x)); 
	
	printf("libc atan =     %19.19f\n", atan(x)); 
	*/

        return 0;
}

