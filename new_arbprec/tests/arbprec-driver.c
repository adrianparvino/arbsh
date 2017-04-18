#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arbprec/arbprec.h>

int base = 10; 		/* global base */

int main(int argc, char **argv)
{ 
	
	int o = 0;
	double a = 0;
	double b = 0;

	while ((o = getopt (argc, argv, "vb:")) != -1)
		switch (o) { 
			case 'v':
				verbosity(NULL, NULL, 1, 0);
				break;
			case 'b': /* Override base */
				base = strtoul(optarg, 0, 10);
				break;
			default:
				break;
		}

	argv += optind;
	argc -= optind;


	if ( argc < 2 )
		die("Needs 2 args\n");

	a = strtod(argv[0], 0);
	b = strtod(argv[1], 0);

	printf("  %20lf\n", a);

	printf("  %20lf\n", b);
	printf("  %20s\n", "-------------------");
	printf("+ %20lf\n", a + b);
	printf("- %20lf\n", a - b);
	printf("* %20lf\n", a * b);
	printf("/ %20lf\n", a / b);

	
	bigflt *flt1 = str_to_bigflt(argv[0]);
	bigflt *flt2 = str_to_bigflt(argv[1]);
	bigflt *flt3 = arba_alloc(1000);

	flt3 = arbprec_add(flt1, flt2, flt3);
	arbprec_print(flt3);

	flt3 = arbprec_sub(flt1, flt2, flt3);
	arbprec_print(flt3);

	flt3 = arbprec_mul(flt1, flt2, flt3);
	arbprec_print(flt3);


	return 0;
}
