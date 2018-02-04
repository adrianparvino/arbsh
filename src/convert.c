#include <arbprec/arbprec.h>
#include <stdint.h>
#include <math.h>

fxdpnt *convscaled(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	char digi[] = "0123456789ABCDEF";
	arb_copy(b, a);
	long long carry = 0;
	long long prod = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t digit = 0;

	// integer
	if (ibase > obase)
		k = (size_t) ((2*a->lp) / log10(obase));
	else 
		k = a->lp;

	b = arb_expand(b, k);
	memset(b->number, 0, k*sizeof(ARBT)); // something is wrong with arb_expand
	b->len = b->lp = k;

	for (i = 0; i < k; ++i) {
		if ( i >= k-(a->lp))
			carry = a->number[i-(k-(a->lp))];
		else
			carry = 0;
		prod = 0;
		for (j = k; j > 0; j--) {
			prod = (b->number[j-1] * ibase) + carry;
			b->number[j-1] = prod % obase;
			carry = prod / obase;
		}
	}

	// non-integer
	fxdpnt *ob = hrdware2arb(obase);
	fxdpnt *ofrac = arb_expand(NULL, rr(a)*2);
	memcpy(ofrac->number, a->number + a->lp, rr(a) * sizeof(ARBT));
	ofrac->len = rr(a);
	ofrac->lp = 0;
	fxdpnt *z = arb_expand(NULL, a->lp);
	fxdpnt *t = arb_str2fxdpnt("1");
	for (i = 0; t->len <= rr(a); ++i) {
		ofrac = arb_mul(ofrac, ob, ofrac, ibase, 10);
		digit = fxd2sizet(ofrac, 10);
		z = hrdware2arb(digit);
		ofrac = arb_sub(ofrac, z, ofrac, 10);
		b = arb_expand(b, (b->lp + i));
		b->number[b->lp + i] = digi[digit];
		b->len++;
		t = arb_mul(t, ob, t, 10, 10);
        }
	b = remove_leading_zeros(b);
	return b;
}
