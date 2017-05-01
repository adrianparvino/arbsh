#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <arbprec/arbprec.h> 


int main(int argc, char **argv)
{
	scale = 10;
	
	if ( argc < 3 )
		arbprec_die("Needs 2 args\n");

	double a = strtod(argv[1], 0);
	double b = strtod(argv[2], 0);

	printf("\n\n\ninternal libm:\n__________\n\n");
	printf("  %20.10lf\n", a);
	printf("  %20.10lf\n", b);
	printf("  %15s\n", "-------------------");
	printf("+ %20.10lf\n", a + b);
	printf("- %20.10lf\n", a - b);
	printf("* %20.10lf\n", a * b);
	printf("/ %20.10lf\n", a / b);
	printf("# %20.10lf\n", sqrt(a));
	printf("\n\narbprec:\n___________\n\n");
	fflush(stdout);

	bigflt *flt1 = str_to_bigflt(argv[1]);
	bigflt *flt2 = str_to_bigflt(argv[2]);

	//flt1 = arbprec_add_precision(flt1, scale);
	//arbprec_match_precision(flt1, flt2);


	bigflt *flt3 = arbprec_expand_vector(NULL, flt1->len + flt2->len);
	/*
	flt3 = arbprec_add(flt1, flt2, flt3);
	arbprec_print(flt3);

	flt3 = arbprec_sub(flt1, flt2, flt3);
	arbprec_print(flt3);

	flt3 = arbprec_mul(flt1, flt2, flt3);
	arbprec_print(flt3); 
	
	flt3 = arbprec_div(flt1, flt2, flt3);
	arbprec_print(flt3);
	*/
	//flt1 = arbprec_add_precision(flt1, scale);
	flt3 = arbprec_sqrt(flt1);
	arbprec_print(flt3);

	//arba_free(flt1);
	//arba_free(flt2);
	//arba_free(flt3);

	printf("\n\n");

	return 0;
}

