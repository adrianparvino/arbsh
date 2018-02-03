#include <arbprec/arbprec.h>
/*
	Copyright 2018  Adrian Parvin D. Ouano  "arb_exp"
*/
fxdpnt *arb_exp(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, size_t scale)
{
	fxdpnt *zero = hrdware2arb(0);
	fxdpnt *one  = hrdware2arb(1);
	fxdpnt *two  = hrdware2arb(2);

	fxdpnt  *b_, *b__, *c_;
	//fxdpnt *b_  = arb_expand(NULL, MAX(scale, b->rp));
	//fxdpnt *b__ = arb_expand(NULL, MAX(scale, b->rp));
	
	c = arb_expand(c, MAX(scale, a->len * b->len + 1));
	//fxdpnt *c_ = arb_expand(NULL, MAX(scale, c->rp));

	for (arb_copy(b_, b), arb_copy(c, one);             // b_ = b; c = 1
	     arb_compare(b_, one, base) > 0;                // b_ > 1
	     arb_sub(b_, two, b__, base), arb_copy(b_, b__) // b_ -= 2;
	     )
	{
		arb_mul(c , a, c_, base, scale);
		arb_mul(c_, a, c , base, scale);
	}
	if (arb_compare(b_, zero, base) > 0)
	{
		arb_copy(c_, c);
		arb_mul(c_, a, c, base, scale);
	}
	
 
	arb_free(two);
	arb_free(one);
	arb_free(zero);

	return c;
}


fxdpnt *arb_exp2(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, size_t scale)
{
	fxdpnt *zero = hrdware2arb(0);
	fxdpnt *one  = hrdware2arb(1);
	fxdpnt *two  = hrdware2arb(2);

	if (arb_compare(b, zero, base) < 0) {
		c = arb_expand(c, 1);
		a = arb_alg_d(one, a, c, base, scale);
		arb_flipsign(b);
	}
	if (arb_compare(b, zero, base) == 0) {
		return one;
	}
	fxdpnt *r = arb_expand(NULL, 1);
	arb_copy(r, one);
	while (arb_compare(b, one, base) > 1) {
		if (arb_compare((c = arb_mod(b, two, c, base, scale)), two, base) == 0) {
			a = arb_mul(a, a, c, base, scale);
			b = arb_alg_d(b, two, c, base, scale);
		} else {
			r = arb_mul(a, r, c, base, scale);
			a = arb_mul(a, a, c, base, scale);
			b = arb_alg_d(arb_sub(b, one, c, base), two, c, base, scale);
		}
	}

	return c;
}
