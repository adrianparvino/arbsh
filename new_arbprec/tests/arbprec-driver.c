#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arbprec/arbprec.h>

size_t cardinal;	/* declare a global cardinal */
int base = 10; 		/* global base */

int main(int argc, char **argv)
{
	int *hold;	/* Copy of bigint1 */
	int *hold2;	/* Copy of bigint2 */
	double a = 0;
	double b = 0;
	int o = 0;
	size_t carda;
	size_t cardb; 
	int *bigint1;			/* Copy of argument 1 */
	int *bigint2;			/* Copy of argument 2 */
	size_t real_cardinality = 0;
	size_t imag_cardinality = 0;
	int *result;

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
	

	mirror = strallocate(1000 * sizeof(int));
	result = strallocate(1000 * sizeof(int));
	bigint1 = strallocate(1000 * sizeof(int));
	bigint2 = strallocate(1000 * sizeof(int));

	/* arb divide */
	printf("division\n");
	carda = strlen(argv[0]);
	cardb = strlen(argv[1]);
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold[carda] = 4242;
	hold2[cardb] = 4242;
	result = divide(hold, hold2, result);

	if ( carda + 1 > cardb )
                real_cardinality = carda - cardb + 1;
        else
                real_cardinality = carda;

        if ( carda >= real_cardinality )
                imag_cardinality = carda - real_cardinality;

        printarray(result, real_cardinality);

        printarray(result + (real_cardinality) ,imag_cardinality);


	/* multiply */
	printf("multiplication\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	result = multiply(hold, hold2, result);
	printarray(result, carda + cardb);

	/* add */
	printf("addition\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold = addition(hold, hold2, result);
	printarray(hold, cardinal);
	
	/* subtract */
	printf("subtraction\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold = subtraction(hold, hold2, result);
	printarray(hold, cardinal);
	
	/* setarray, iszero, arb copyarray */
	printf("setarray. iszero, copyarray\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	setarray(hold, 0);
	setarray(hold2, 1);
	printarray(hold, cardinal);
	printarray(hold2, cardinal);
	if ( iszero(hold) == 0 )
		printf("hold is zero\n");
	if ( iszero(hold2) != 0 )
		printf("hold2 is not zero\n");
	copyarray(hold2, hold);
	if ( iszero(hold2) == 0 )
		printf("hold2 is now zero\n");

	return 0;
} 

