#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
	if (argc < 4 )
		arb_error("Needs 3 args, such as:  123 / 123 base");
 
	
	int base = strtol(argv[3], 0, 10);
	fxdpnt *a, *b, *c;
	a = arb_str2fxdpnt(argv[1]);
	b = arb_str2fxdpnt(argv[2]);
	c = arb_expand(NULL, 1);
	a = arb_add(a, a, a, base);
	arb_print(a);
	arb_free(a);
	arb_free(b);
	arb_free(c);

	return 0;
}

