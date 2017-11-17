#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	
	if (argc < 4 )
		return 0;
	double N = strtod(argv[1], 0);
	double D = strtod(argv[2], 0);
	double F = strtod(argv[3], 0);
	size_t i = 0;

	printf("F == %lf\n", F);

	
	while ( D >= 1.0000000000000 )
	{
		N *= F;
		D *= F;
		printf("N == %lf\n", N);
		printf("D == %lf\n", D);
		++i;
	}
	printf("%zu iterations\n", i);
	printf("answer N == %lf\n", N);
	printf("D == %lf\n", D);

	return 0;
}
