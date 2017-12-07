#include <arbprec/arbprec.h>

size_t arb_mul_core(ARBT *a, size_t alen, ARBT *b, size_t blen, ARBT *c, int base)
{
	int i = 0, j = 0, sum = 0, carry = 0;
        size_t k = 0;
	size_t last = 0;
	size_t ret = blen;
	c[k] = 0;
	c[alen + blen -1] = 0;
	for ( i = alen - 1; i >= 0 ; i--){
		last = k;
		for ( j = blen - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--){
			sum = (a[i]) * (b[j]) + (c[k]) + carry;
			carry = sum / base; 
			c[k] = (sum % base);
		}
		if (k != last)
		{
		++ret;	
			c[k] = 0;
		}
		
		c[k] += carry;
	}
	return ret;
}

fxdpnt *arb_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	size_t scale = 0;
	arb_setsign(a, b, c);
	c = arb_expand(c, a->len + b->len);
	arb_mul_core(a->number, a->len, b->number, b->len, c->number, base);
	c->lp = a->lp + b->lp;
	c->rp = a->rp + b->rp;
	c->rp = MAX(a->rp, b->rp);
	c->rp = MIN(a->rp + b->rp, maxi(20, a->rp, b->rp));
	c->len = c->rp + c->lp;
	return c;
}

