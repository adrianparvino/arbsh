#include <arbprec/arbprec.h>

void print_arbt(FILE *fp, ARBT *number, size_t len, size_t radix)
{
	size_t i = 0;
	for (i=0; i < len ; ++i)
	{
		if (radix == i)
			fprintf(fp, ".");
		fprintf(fp, "%c", arb_highbase((number[i])));
	}
	fprintf(fp, "\n");
	fflush(fp);
}

void arb_printold(fxdpnt *flt)
{
        size_t i = 0;
        if (flt->sign == '-')
                putchar(flt->sign);
	print_arbt(stdout, flt->number, flt->len, flt->lp);
}

void arb_print(fxdpnt *flt)
{
        size_t i = 0;
	size_t len = 0;
	flt->len = flt->lp + flt->rp;

	if (flt->len == 0)
		len = flt->lp + flt->rp;
	else
		len = flt->len;

        if (flt->sign == '-')
                putchar(flt->sign);
	print_arbt(stdout, flt->number, flt->len, flt->lp);
}
