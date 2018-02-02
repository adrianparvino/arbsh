#include <arbprec/arbprec.h>
#include "fxdpnt.h"

fxdpnt *arb_mod(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, size_t scale)
{
	size_t newscale = MAX(a->len, b->len + scale);
	fxdpnt *tmp = arb_expand(NULL, newscale);
	tmp = arb_alg_d(a, b, tmp, base, scale);
	tmp = arb_mul(tmp, b, tmp, base, newscale);
	c = arb_sub(a, tmp, c, base);
	free(tmp);
	return c;
}
