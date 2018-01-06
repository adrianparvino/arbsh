#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	size_t len = floor(log2(strtod(argv[1], 0)));
	printf("len = %zu\n", len);
	
	len = floor(log10(strtod(argv[1], 0)));
	printf("len = %zu\n", len);
	
	double nlen = log10(strtod(argv[1], 0));
	printf("nlen = %f\n", nlen);

	double con = log(10)/log(2);
	printf("con = %f\n", con);
	return 0;
}
