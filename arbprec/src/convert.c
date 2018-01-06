#include <arbprec/arbprec.h>

fxdpnt *convert(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	arb_copy(b, a);
	ARBT *p;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	int notdone = 1;
	p = arb_calloc(a->len, sizeof(ARBT));
	ARBT *array = arb_calloc(a->len, sizeof(ARBT));
	memcpy(array, a->number, a->len * sizeof(ARBT));
	for (; i < a->len + k || notdone; i++)
	{ 
		notdone = 1;
		int carry = array[i];
		int prod = 0;
		for (j = a->len + k; j > 0; j--) {
			prod = (p[j-1] * ibase) + carry;
			p[j-1] = prod % obase;
			carry = prod / obase;
		}

		if (carry)
		{
			++k;
			array = realloc(array, (a->len + k) * sizeof(ARBT));
			p = realloc(p, (a->len + k) * sizeof(ARBT));
			memset(p, 0, (a->len + k) * sizeof(ARBT));
			rightshift_core(array, a->len + k, 1);
			b->len++;
			b->lp++;
			i = 0;
		}else
			notdone = 0;
	}
	b->number = p;

	return b;
}

