#include <arbprec/arbprec.h>

void arb_mul_core(ARBT *a, size_t alen, ARBT *b, size_t blen, ARBT *c, int base)
{
	int i = 0, j = 0, sum = 0, carry = 0;
        size_t k = 0;
	size_t last = 0;
	c[k] = 0;
	c[alen + blen -1] = 0;
	//memset(c, 0, (alen + blen) * sizeof(ARBT));
	for ( i = alen - 1; i >= 0 ; i--){
		last = k;
		for ( j = blen - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--){
			sum = (a[i]) * (b[j]) + (c[k]) + carry;
			carry = sum / base; 
			c[k] = (sum % base);
		}
		if (k != last)
			c[k] = 0;
		c[k] += carry;
	}
}

fxdpnt *arb_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	arb_setsign(a, b, c);
	c = arb_expand(c, a->len + b->len);
	// arb_mul_core is self zeroing, remove this ASAP
	memset(c->number, 0, (a->len + b->len) * sizeof(ARBT));
	arb_mul_core(a->number, a->len, b->number, b->len, c->number, base);
	c->len = a->len + b->len;
	c->lp = a->lp + b->lp;
	c->rp = c->rp + c->rp; // untested. however, every function needs to set rp as well as lp
	return c;
}

