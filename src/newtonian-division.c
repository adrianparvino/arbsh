#include <arbprec/arbprec.h>

fxdpnt *arb_newtonian_div(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	size_t i = 0;
	fxdpnt *guess = arb_expand(NULL, a->len);
	fxdpnt *newguess = arb_expand(NULL, 1); 
	fxdpnt *hold = arb_expand(NULL, a->len);
	fxdpnt *two = arb_str2fxdpnt("2.00000");

	guess->lp = 0;
	guess->rp = a->len;
	memset(guess->number, 0, a->len * sizeof(ARBT));
	guess->number[a->len -1] = 5;
	guess->len = a->len;
	
	for(i=0;i < 100000;++i)
	{ 
		hold = arb_mul(b, guess, hold, base, scale);
		hold = arb_sub(two, hold, hold, base);
		newguess = arb_mul(guess, hold, newguess, base, scale);
		if (arb_compare(guess, newguess, base) == 0)
                        break;
		arb_copy(guess, newguess);
	}
	c = arb_expand(c, guess->len + a->len);
	c = arb_mul(guess, a, c, base, scale);
	return c;
}

