#include <arbprec/arbprec.h>
#include <stdint.h>
#include <math.h>

fxdpnt *convert(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	arb_copy(b, a);
	ARBT *p;
	ARBT carry = 0;
	ARBT prod = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	/* TODO: use an algorithm that doesn't require log() for # digits */
	if (ibase > obase && obase < 50)
		/* ln(x) / ln(base) == ln_base(x) */
		k = (size_t) (a->len / log10(obase));
	else 
		k = a->len;
	p = arb_calloc(k, sizeof(ARBT));
	ARBT *array = arb_calloc(k, sizeof(ARBT));
	memcpy(array + (k - a->len), a->number, a->len * sizeof(ARBT));
	memset(array, 0, (k - a->len) * sizeof(ARBT));

	for (; i < k; ++i) { 
		carry = array[i];
		prod = 0;
		for (j = k; j > 0; j--) {
			prod = (p[j-1] * ibase) + carry;
			p[j-1] = prod % obase;
			carry = prod / obase;
		}
	}
	b->number = p;
	b->len = k;
	b->lp = k;
	return b;
}

fxdpnt *conv_frac(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	arb_copy(b, a);
	ARBT *p;
	ARBT *o;
	size_t i = 0;
	size_t k = 0;
	char obasehold[1000];
	size_t len = 0;
	size_t z = a->len;
	size_t size = 0;

	sprintf(obasehold, "%d", obase);
	fxdpnt *obh = arb_str2fxdpnt(obasehold);
	
	k = a->len;
	p = arb_calloc(k * 2, sizeof(ARBT));
	o = arb_calloc(k * 2, sizeof(ARBT));
	
	ARBT *array = arb_calloc(z * 2, sizeof(ARBT));
	memcpy(array, a->number, a->len * sizeof(ARBT));
	for (; i < k; ++i) {
		memset(o, 0, z * sizeof(ARBT)); 
		len = arb_mul_core(array, z, obh->number, obh->len, o, ibase);
		size = len - z;
		p[i] = arb2hrdware(o, size , 10); /* note: absorbs leading zeros */
		_arb_copy_core(array, o + size , z);
        }

	b->number = p;
	b->len = z;
	b->lp = 0; 
	
	return b;
}

