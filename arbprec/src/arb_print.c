#include <arbprec/arbprec.h>

void _print_core(FILE *fp, ARBT *number, size_t len, size_t radix)
{
	size_t i = 0;
	for (i=0; i < len ; ++i){
		if (radix == i)
			fprintf(fp, ".");
		fprintf(fp, "%c", arb_highbase((number[i])));
	}
	fprintf(fp, "\n");
	fflush(fp);
}

void arb_print(fxdpnt *flt)
{
	if (flt->sign == '-')
		putchar(flt->sign);
	_print_core(stdout, flt->number, flt->len, flt->lp);
}

