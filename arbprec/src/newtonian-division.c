#include <arbprec.h>

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
	(void)scale; // scale will never be needed
	fxdpnt *guess = arb_expand(NULL, a->len + b->len);
	fxdpnt *newguess = arb_expand(NULL, a->len + b->len);
	fxdpnt *hold = arb_expand(NULL, a->len + b->len);
	fxdpnt *hold2 = arb_expand(NULL, a->len + b->len);
	fxdpnt *two = arb_str2fxdpnt("2");;
	fxdpnt *reciprocal;

	guess->lp = 0;
	guess->rp = a->len + b->len;
	memset(guess->number, 0, a->len + b->len);
	guess->number[a->len + b->len -1] = 5;

	arb_printold(guess);
	
	size_t i = 0;
	while (i < 100)
	{
		hold = arb_mul(a, guess, hold, base); // x * guess
		hold2 = arb_sub(hold, two, hold2, base); // 2 - x * guess
		newguess = arb_mul(guess, hold2, newguess, base);
		++i;
	}
	reciprocal = guess;
	c = arb_mul(reciprocal, b, c, base);
	return c;
}
