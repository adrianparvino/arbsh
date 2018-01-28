#include <arbprec/arbprec.h>

void _arb_copy_core(ARBT *b, ARBT *a, size_t len)
{
	//memcpy(b, a, len * sizeof(ARBT));
	size_t i = 0;
	for (i=0;i < len;++i)
		b[i] = a[i];
}

void arb_copy(fxdpnt *b, fxdpnt *a)
{ 
	b = arb_expand(b, a->len);

	//b->number = arb_malloc(a->len);
	//b->allocated = a->allocated;
	b->len = a->len;
	b->rp = a->rp;
	b->lp = a->lp;
	//b->chunk = b->chunk;
	b->sign = a->sign;
	_arb_copy_core(b->number, a->number, a->len);
}

