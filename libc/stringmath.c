#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stdlib/stdlib.h"
#include "arb_str_math/arb_str.h"
/* functions */
int main(int argc, char *argv[])
{
	int o = 0;
	while ((o = getopt (argc, argv, "v")) != -1)
                switch (o) { 
			case 'v': 
				arb_str_verbosity = 1;
                                break; 
                        default: 
				break;
                }

        argv += optind;
        argc -= optind;

	
	if ( argc < 2) 
		arb_str_die("Please provide two numbers\n"); 

	char *a = gstrdup(argv[0]);
	char *b = gstrdup(argv[1]);
	size_t len = (gstrlen(a) + gstrlen(b) + 10);
	char *d;
	char *z;
	char *y;

	y = d = gmalloc(len);
	z = mirror = gmalloc(len);
	tmpmir = gmalloc(len);

	printf("\n\n");
        printf("         %20s\n", a);
        printf("+,-,*,/  %20s\n", b);
	printf("         %20s\n", "-------------------");

	arb_str_verbosity = 1;

	//d[0] = '+';
	//d = arb_str_add(a, b, d);
	//printf("result(add) = %20s\n", d); 
	//printf("answer      = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10)); 

	//d[0] = '+';
	//d = arb_str_subtract(a, b, d);
	//printf("result(sub) = %20s\n", d);
	//printf("answer      = %20ld (subtraction) \n", strtol(a, 0, 10) - strtol(b, 0, 10)); 

	//d[0] = '+';
	//d = arb_str_multiply(a, b, d);
	//printf("result(mul) = %20s\n", d);
	//printf("answer      = %20ld (multiplication) \n", strtol(a, 0, 10) * strtol(b, 0, 10));

	//d[0] = '+';
	
	d[0] = '0';
	d = arb_str_divide(a, b, d);
	printf("result(div) = %s\n", d);
	printf("answer      = %lf (division) \n", strtod(a, 0) / strtod(b, 0));

	gfree(d = y);
	gfree(mirror = z);
	gfree(tmpmir);
} 
