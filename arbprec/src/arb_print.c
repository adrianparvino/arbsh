#include <arbprec/arbprec.h>

int arb_highbase(int a)
{
	// Handle high bases
	static int glph[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
				'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
				'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
				'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	if (a < 36) 
		return glph[a]; 
	else // just use the ascii values for bases that are very high
		return a;
}

void _print_core(FILE *fp, ARBT *number, size_t len, size_t radix)
{
	size_t i = 0;
	int state = 0;
	size_t k = 0;
	for (i=0; i < len ; ++i){
		if (number[i] == 0 && state == 0 && i < radix)
			continue;
		state = 1;
		
		if (k % 68 == 0 && k != 0)
			fprintf(fp, "\\\n");
		
		if (radix == i)
		{ 
			fprintf(fp, ".");
			++k;
		}
		fprintf(fp, "%c", arb_highbase((number[i])));
		++k;
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
