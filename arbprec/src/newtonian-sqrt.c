#include <arbprec/arbprec.h>

fxdpnt *arb_newton_sqrt(fxdpnt *a, fxdpnt *c, int base, int scale)
{
	fxdpnt *new_guess = NULL;
	new_guess = arb_expand(new_guess, a->len);
	
	fxdpnt *guess = NULL;
	guess = arb_expand(guess, a->len);
	guess->number[0] = 5;
	//guess->number[0] = 5;
	printf("%zu size\n", guess->len);
	fxdpnt *ans = NULL;
	ans = arb_expand(ans, a->len);
	
	fxdpnt *hold = NULL;
	hold = arb_expand(hold, a->len);

	fxdpnt *p5 = NULL;
	p5 = arb_str2fxdpnt("0.5");
	printf("here\n");
	size_t i = 0;
	while (i++ < 10)
	{
		arb_copy(new_guess, guess);
		printf("step1\n");
		printf("%zu a\n", a->len);
		printf("%zu ans\n", ans->len);
		printf("%zu size\n", guess->len);
		ans = arb_alg_d(a, guess, ans, base, scale);
		printf("step2\n");
		hold = arb_add(ans, new_guess, hold, base);
		printf("middle\n");
		guess = arb_mul(hold, p5, guess, base);
		if (arb_compare(guess, new_guess, base) == 0)
			break;
		arb_print(guess);
		printf("bottom\n");
	}
	c = guess;
	return c;
}
