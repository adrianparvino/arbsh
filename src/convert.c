#include <arbprec/arbprec.h>
#include <stdint.h>
#include <math.h>

fxdpnt *convscaled(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	char digi[] = "0123456789ABCDEF";
	arb_copy(b, a);
	ARBT *sv;
	long long carry = 0;
	long long prod = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t z = 0;
	size_t digit = 0;
	
	ARBT *p;

	// real
	if (ibase > obase)
		k = (size_t) ((2*a->lp) / log10(obase)) ;
	else 
		k = a->lp;
	sv = arb_calloc(k, sizeof(ARBT));
	ARBT *real = arb_calloc(k, sizeof(ARBT));
	memcpy(real + (k - a->lp), a->number, a->lp * sizeof(ARBT));
	memset(real, 0, (k - a->lp) * sizeof(ARBT));

	for (i = 0; i < k; ++i) { 
		carry = real[i];
		prod = 0;
		for (j = k; j > 0; j--) {
			prod = (sv[j-1] * ibase) + carry;
			sv[j-1] = prod % obase;
			carry = prod / obase;
		}
	}
	b = arb_expand(b, k);
	_arb_copy_core(b->number, sv, k);
	b->len = k;
	b->lp = k;
	
	// fractional
	fxdpnt *obh = hrdware2arb(obase);
	fxdpnt *ofrac = arb_expand(NULL, rr(a)*2);
	memcpy(ofrac->number, a->number + a->lp, rr(a) * sizeof(ARBT));
	ofrac->len = rr(a);
	ofrac->lp = 0;
	fxdpnt *intpart = arb_expand(NULL, a->lp);
	fxdpnt *t = arb_str2fxdpnt("1");
	for (i = 0; t->len <= rr(a); ++i) {
		ofrac = arb_mul(ofrac, obh, ofrac, ibase, 10);
		digit = fxd2sizet(ofrac, 10);
		intpart = hrdware2arb(digit);
		ofrac = arb_sub(ofrac, intpart, ofrac, 10);
		b = arb_expand(b, (b->lp + i));
		b->number[b->lp + i] = digi[digit];
		t = arb_mul(t, obh, t, 10, 10);
        }
	b->len = b->lp + i;
	b = remove_leading_zeros(b);
	return b;
}
