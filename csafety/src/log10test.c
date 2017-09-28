#include <stdio.h>
#include <math.h>

int main(void)
{
	double x = 12;
	int base = 10;
	printf("%lf\n", x);
	printf("%lf\n", log10(x));
	printf("%lf\n", floor(log10(x)));
	printf("%lf\n", floor(log10(x))+1);
	printf("%lf\n", (pow(base, floor(log10(x))+1)-1));

	return 0;
}

