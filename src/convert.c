#include <arbprec/arbprec.h>
#include <stdint.h>
#include <math.h>
fxdpnt *convall(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
        arb_copy(b, a);
        ARBT *sv;
        long long carry = 0;
        long long prod = 0;
        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        size_t z = 0;
        size_t len = 0;
        size_t size = 0;

        ARBT *p;
        ARBT *o;

        /* real */
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

        /* fractional */
        z = rr(a);
        fxdpnt *obh = hrdware2arb(obase);
        p = arb_calloc(z * 2, sizeof(ARBT));
        o = arb_calloc(z * 2, sizeof(ARBT));

        ARBT *frac = arb_calloc(z * 2, sizeof(ARBT));
        memcpy(frac, a->number + a->lp, rr(a) * sizeof(ARBT));

        for (i = 0; i < z; ++i) {
                memset(o, 0, z * sizeof(ARBT));
                len = arb_mul_core(frac, z, obh->number, obh->len, o, ibase);
                size = len - z;
                p[i] = arb2hrdware(o, size , 10); /* note: absorbs leading zeros */
                _arb_copy_core(frac, o + size , z);
        }
        size_t total = z;
        b = arb_expand(b, (b->lp + total));
        _arb_copy_core(b->number + b->lp, p, total);
       // b->rp = total;

        /* finish off */
        //b->len = b->lp + b->rp;
	b->len = b->lp + total;
        return b;
}
/*
fxdpnt *convscaled(fxdpnt *a, fxdpnt *b, int ibase, int obase, size_t scale)
{
	scale = scale; // get rid of compiler warnings until this is used
	arb_copy(b, a);
	ARBT *sv;
	long long carry = 0;
	long long prod = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t z = 0;
	
	size_t size = 0;
	
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
	z = a->rp;
	fxdpnt *obh = hrdware2arb(obase);
	p = arb_calloc(z * 2, sizeof(ARBT));
	//o = arb_calloc(z * 2, sizeof(ARBT));
	fxdpnt *oo = arb_expand(NULL, z*2);
	fxdpnt *ofrac = arb_expand(NULL, z*2);
	
	
	
	memcpy(ofrac->number, a->number + a->lp, a->rp * sizeof(ARBT));
	ofrac->len = a->rp;
	ofrac->lp =  a->rp;
	a->rp = 0;

	
	// use the following formula for scale
	// while (hold->len <= scale)
	// multiply (hold, base, ....);
	for (i = 0; i < z; ++i) { 
		memset(oo->number, 0, z * sizeof(ARBT)); 
		oo = arb_mul(ofrac, obh, oo, ibase, 10);
		size = oo->len - z; 
		p[i] = arb2hrdware(oo->number, size , 10);
		_arb_copy_core(ofrac->number, oo->number + size, z);
        }
	size_t total = z;
	b = arb_expand(b, (b->lp + total));
	_arb_copy_core(b->number + b->lp, p, total);
	b->rp = total;
	
	// finish off
	b->len = b->lp + b->rp;
	return b;
}
*/
