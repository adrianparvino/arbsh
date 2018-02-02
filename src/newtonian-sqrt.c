#include <arbprec/arbprec.h>
#include "fxdpnt.h"

fxdpnt *arb_newton_sqrt(fxdpnt *a, fxdpnt *c, int base, int scale)
{
	size_t i = 0;
	fxdpnt *new_guess;
	fxdpnt *guess;
	fxdpnt *ans;
	fxdpnt *hold;
	fxdpnt *p5 = NULL;

	new_guess = arb_expand(NULL, a->len);
	guess = arb_expand(NULL, a->len);
	arb_copy(guess, a);
	ans = arb_expand(NULL, a->len);
	hold = arb_expand(NULL, a->len);
	p5 = arb_str2fxdpnt("0.5"); 
	fxdpnt *two = arb_str2fxdpnt("2.0"); 
	
	for (i=0;i < 1000;++i)
	{
		arb_copy(new_guess, guess);
		ans = arb_alg_d(a, guess, ans, base, scale);
		hold = arb_add(ans, new_guess, hold, base);
		guess = arb_mul(hold, p5, guess, base, scale);
		//guess = arb_alg_d(hold, two, guess, base, scale);
		if (arb_compare(guess, new_guess, base) == 0)
			break;
	
	}
	c = guess;
	return c;
}


