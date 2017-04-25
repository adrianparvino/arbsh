#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arbprec/arbprec.h> 


int main(int argc, char **argv)
{

	if ( argc < 3 )
		die("Needs 2 args\n");

	double a = strtod(argv[1], 0);
	double b = strtod(argv[2], 0);

	printf("  %20.10lf\n", a);
	printf("  %20.10lf\n", b);
	printf("  %20s\n", "-------------------");
	printf("+ %20.10lf\n", a + b);
	printf("- %20.10lf\n", a - b);
	printf("* %20.10lf\n", a * b);
	printf("/ %20.10lf\n", a / b);
	fflush(stdout);

	bigflt *flt1 = str_to_bigflt(argv[1]);
	bigflt *flt2 = str_to_bigflt(argv[2]);
	bigflt *flt3 = arba_alloc(10000);

	flt3 = arbprec_add(flt1, flt2, flt3);
	arbprec_print(flt3);

	flt3 = arbprec_sub(flt1, flt2, flt3);
	arbprec_print(flt3);

	flt3 = arbprec_mul(flt1, flt2, flt3);
	arbprec_print(flt3); 
	
	flt3 = arbprec_div(flt1, flt2, flt3);
	arbprec_print(flt3);

	printf("\n\n");

	return 0;
}

