#include <arbprec/arbprec.h>

void _arb_copy_core(ARBT *b, ARBT *a, size_t len)
{
	memcpy(b, a, len * sizeof(ARBT));
}

void arb_copy(fxdpnt *a, fxdpnt *b, size_t len)
{
	b = arb_expand(b, a->len);
	b->len = a->len;
	b->rp = a->rp;
	b->rp = a->lp;
	_arb_copy_core(b->number, a->number, len);
}

