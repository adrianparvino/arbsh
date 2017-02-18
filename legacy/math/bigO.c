#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		printf("provide an arg\n");
		return 1;
	}
	double a = strtod(argv[1], 0);
	
	printf("If 'a' is %lf thenf\n", a);

	printf("0(1)\n");
	printf("0(%lf)\n", a);
	printf("0(log(%lf) = %lf)\n",a, log(a));
	printf("0(%lf log(%lf) = %lf)\n", a, a, a * log(a));
	return 0;
}


