#include <arbprec/arbprec.h>


fxdpnt *convert(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	arb_copy(b, a);
	ARBT *p;
        size_t i = 0;
        size_t j = 0;
        p = arb_calloc(a->len, sizeof(ARBT));
	ARBT *array = a->number;
        for (; i < a->len; i++)
        { 
                int carry = array[i];
                int prod = 0;
                for (j = a->len; j > 0; j--) {
                        prod = (p[j-1] * ibase) + carry;
                        p[j-1] = prod % obase;
                        carry = prod / obase;
                }
        }
	b->number = p;
	
	return b;
}

