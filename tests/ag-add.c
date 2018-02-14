#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{ 
	// this needs to be have an unused arg to match the testing infrastructure
	if (argc < 4 )
		arb_error("Needs 3 args, such as: 123 123 base");

	int base = strtol(argv[3], 0, 10);
	fxdpnt *a;
	a = arb_str2fxdpnt(argv[1]);
	a = arb_add(a, a, a, base);
	arb_print(a);
	arb_free(a);
	return 0;
}

