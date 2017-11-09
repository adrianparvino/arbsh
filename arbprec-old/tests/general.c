#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <arbprec/arbprec.h> 


int main(int argc, char **argv)
{
	scale = 80;
	
	if ( argc < 3 )
		arbprec_die("Needs 2 args\n");

	double a = strtod(argv[1], 0);
	double b = strtod(argv[2], 0);


	printf("  %20.10lf\n", a);
	printf("  %20.10lf\n", b);
	printf("  %15s\n", "-------------------");

	bigflt *flt1 = str_to_bigflt(argv[1]);
	bigflt *flt2 = str_to_bigflt(argv[2]);


	printf("rr() right of radix %zu\n", rr(flt1));
        printf("rl() left of radix %zu\n", rl(flt1));

	if (arbprec_compare(flt1, flt2) == 1)
		printf("flt1 was larger\n");
	if (arbprec_compare(flt1, flt2) == -1)
		printf("flt2 was larger\n");
	if (arbprec_compare(flt1, flt2) == 0)
		printf("flt1 and flt2 are equal\n");

	return 0;
}
