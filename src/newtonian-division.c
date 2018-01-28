#include <arbprec/arbprec.h>

double newton_iteration(double x, double eps)
{
        double guess = eps;
        double new_guess = 0;
        size_t i = 0;
        while (i < 100)
        {
                // method 1
                new_guess = guess * (2 - x * guess);
                // method 2
                //new_guess = guess + guess * ( 1 - x * guess); 
                if (guess == new_guess)
                        break;
                guess = new_guess;
                printf("%19.19lf\n", new_guess);
                ++i;

        }
        printf("iterations = %zu\n", i);
        return guess;
}

fxdpnt *arb_newtonian_div(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	//(void)scale;
	// experimental function -- not working!!
	fxdpnt *guess = arb_expand(NULL, a->len);
	fxdpnt *newguess = arb_expand(NULL, 1); 
	fxdpnt *hold = arb_expand(NULL, a->len);
	fxdpnt *hold2 = arb_expand(NULL, a->len);
	fxdpnt *two = arb_str2fxdpnt("2.00000");
	fxdpnt *reciprocal;

	guess->lp = 0;
	guess->rp = a->len;
	memset(guess->number, 0, a->len);
	guess->number[a->len -1] = 5;
	guess->len = a->len;
	size_t i = 0;
	while (i < 1000000)
	{ 
		hold = arb_mul(b, guess, hold, base, scale);
		hold = arb_sub(two, hold, hold, base);
		newguess = arb_mul(guess, hold, newguess, base, scale);
		if (arb_compare(guess, newguess, base) == 0)
                        break;
		arb_copy(guess, newguess);
		++i;
	}
	c = arb_expand(c, guess->len + a->len);
	c = arb_mul(guess, a, c, base, scale);
	return c;
}
