#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

void die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

/* functions */
int main(int argc, char *argv[])
{

        if ( argc != 2) 
                die("Please provide a numbers"); 

	char *a = argv[1]; 

	long num = strtold(a, 0);

	long X = num -1;
	size_t i = 0;
	size_t j = 2;

	long res = 0;

	int toggle = -1;

	
        printf("         %20s\n", a); 
	printf("         %ld\n", num); 

	X = 1 - X;

	//res = X;
	while ( i < 7 )
	{
		res = pow(X,j) * toggle;
		//X = X * -X;
		toggle = -toggle;
		++i;
		++j;
	}

	
        printf("         %20s\n", a); 
	printf("         %ld\n",res); 


	//printf("answer      = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10)); 
}
