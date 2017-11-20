#include <arbprec/arbprec.h>

void arb_mul_core(ARBT *a, size_t alen, ARBT *b, size_t blen, ARBT *c, int base)
{
	int i = 0, j = 0, sum = 0, carry = 0;
        size_t k = 0;

	for ( i = alen - 1; i >= 0 ; i--){
		for ( j = blen - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--){
			sum = (a[i]) * (b[j]) + (c[k]) + carry;
			carry = sum / base; 
			c[k] = (sum % base);
		}
		c[k] += carry;
	} 
}

fxdpnt *arb_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	arb_setsign(a, b, c);
	c = arb_expand(c, a->len + b->len);
	memset(c->number, 0, (a->len + b->len) * sizeof(ARBT));
	arb_mul_core(a->number, a->len, b->number, b->len, c->number, base);
	c->len = a->len + b->len;
	c->lp = a->lp + b->lp;
	return c;
}

