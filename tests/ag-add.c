#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
	if (argc < 3 )
		arb_error("Needs 2 args, such as: 123 base");
	
	int base = strtol(argv[2], 0, 10);
	fxdpnt *a;
	a = arb_str2fxdpnt(argv[1]);
	a = arb_add(a, a, a, base);
	arb_print(a);
	arb_free(a);
	return 0;
}

