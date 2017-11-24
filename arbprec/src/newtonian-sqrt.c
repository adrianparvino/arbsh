#include <arbprec/arbprec.h>

fxdpnt *arb_newton_sqrt(fxdpnt *a, fxdpnt *c, int base, int scale)
{
	fxdpnt *new_guess = NULL;
	new_guess = arb_expand(new_guess, a->len);
	
	fxdpnt *guess = NULL;
	guess = arb_expand(guess, a->len);
	guess->number[guess->len -1] = 5;

	fxdpnt *ans = NULL;
	ans = arb_expand(ans, a->len);
	
	fxdpnt *hold = NULL;
	hold = arb_expand(hold, a->len);

	fxdpnt *p5 = NULL;
	p5 = arb_str2fxdpnt("0.5");
	
	while (1)
	{
		arb_copy(new_guess, guess);
		ans = arb_alg_d(a, guess, ans, base, scale);
		guess = arb_add(ans, new_guess, hold, base);
		hold = arb_mul(hold, p5, guess, base);
		if (arb_compare(guess, new_guess, base) == 0)
			break;
		
	}
	c = guess;
	return c;
}
