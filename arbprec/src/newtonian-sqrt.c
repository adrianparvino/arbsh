#include <arbprec/arbprec.h>

fxdpnt *arb_newton_sqrt(fxdpnt *a, fxdpnt *c, int base, int scale)
{
	fxdpnt *new_guess = NULL;
	new_guess = arb_expand(new_guess, a->len); 
	fxdpnt *guess = NULL; 
	guess = arb_expand(guess, a->len /50);
	guess->number[0] = 5; 
	printf("%zu size\n", guess->len);
	fxdpnt *ans = NULL;
	ans = arb_expand(ans, a->len); 
	fxdpnt *hold = NULL;
	hold = arb_expand(hold, a->len); 
	fxdpnt *two = NULL;
	two = arb_str2fxdpnt("2.0");
	size_t i = 0;
	while (i++ < 10000)
	{
		arb_copy(new_guess, guess);
		ans = arb_alg_d(a, guess, ans, base, scale); 
		hold = arb_add(ans, new_guess, hold, base);
		guess = arb_alg_d(hold, two, guess, base, scale);
		if (arb_compare(guess, new_guess, base) == 0)
			break; 
	}
	fprintf(stderr, "%zu iterations\n", i);
	c = guess;
	return c;
}