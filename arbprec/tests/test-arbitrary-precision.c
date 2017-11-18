#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
	if (argc < 5 )
		arb_error("Needs 4 args, such as:  123 / 123 base scale");
 
	size_t scale =  strtol(argv[4], 0, 10);
	int base = strtol(argv[3], 0, 10);
	fxdpnt *a, *b, *c;

	a = arb_str2fxdpnt(argv[1]);
	b = arb_str2fxdpnt(argv[2]);
	
	//a = arb_add_precision(a, scale);
	//b = arb_add_precision(b, scale);
	c = arb_expand(NULL, 1);
	printf("mul\n");
	c = arb_mul(a, b, c, base);
	arb_printold(c);
	printf("div\n");
	c = arb_division(a, b, c, base, scale);
	arb_printold(c);
	printf("add\n");
	c = arb_add(a, b, c, base);
	arb_printold(c);
	printf("sub\n");
	c = arb_sub(a, b, c, base);
	arb_printold(c);
	arb_print(a);
	arb_rightshift(a, 1, 0);
	arb_print(a);
	arb_rightshift(a, 3, 0);
	arb_print(a);
	arb_free(a);
	arb_free(b);
	arb_free(c);

	return 0;
}

