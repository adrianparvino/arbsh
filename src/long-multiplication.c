#include <arbprec/arbprec.h>

size_t arb_mul_core(ARBT *a, size_t alen, ARBT *b, size_t blen, ARBT *c, int base)
{
	ARBT prod = 0, carry = 0;
	size_t i = 0;
	size_t j = 0;
        size_t k = 0;
	size_t last = 0;
	size_t ret = blen;
	c[k] = 0;
	c[alen + blen -1] = 0;
	for (i = alen; i > 0 ; i--){
		last = k;
		for (j = blen, k = i + j, carry = 0; j > 0 ; j--, k--){
			prod = (a[i-1]) * (b[j-1]) + (c[k-1]) + carry;
			carry = prod / base;
			c[k-1] = (prod % base);
		}
		if (k != last) {
			++ret;	
			c[k-1] = 0;
		}
		c[k-1] += carry;
	}
	return ret;
}

fxdpnt *arb_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, size_t scale)
{
	arb_setsign(a, b, c);
	c = arb_expand(c, a->len + b->len);
	fxdpnt *a2 = arb_expand(NULL, MAX(scale, a->len));
	fxdpnt *b2 = arb_expand(NULL, MAX(scale, b->len));
	fxdpnt *c2 = arb_expand(NULL, a->len + b->len);
	arb_copy(a2, a);
	arb_copy(b2, b);
	arb_mul_core(a2->number, a2->len, b2->number, b2->len, c2->number, base);
	arb_copy(c, c2);
	c->lp = a2->lp + b2->lp;
	c->rp = MIN(a2->rp + b2->rp, MAX(scale, MAX(a2->rp, b2->rp)));
	c->len = c->rp + c->lp;
	c = remove_leading_zeros(c);
	arb_free(a2);
	arb_free(b2);
	arb_free(c2);
	return c;
}

