

#include <stdio.h>  
#include <math.h>   /* for comparative testing */
#include "addition.c"
#include <stdlib.h> /* for strtod */ 
#include <float.h>
#include <stdint.h>




int main(int argc, char *argv[])
{ 


	double arg1 = 0;
	double arg2 = 0; 

	if ( argc != 3 )
	{
		printf("please supply 2 numerical arguments\n");
		return 1;
	}

	arg1 = strtod(argv[1], 0);
        arg2 = strtod(argv[2], 0);

	printf("addition() = %lf\n", addition(arg1, arg2));
	printf("+ %lf\n", arg1 + arg2);
	
	printf("multiplication() = %lf\n", multiplication(arg1, arg2));
	printf("* %lf\n", arg1 * arg2);
	
}
