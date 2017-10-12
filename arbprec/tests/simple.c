#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	double a = strtof(argv[1], 0);
	double b = strtof(argv[2], 0);
	printf("%lf %lf\n", a, b);
	printf("%lf\n", a + b);
	printf("%lf\n", a * b);
}

