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
void arb_copy(fxdpnt *dest, fxdpnt *src)
{ 
	dest = arb_expand(dest, src->len);
	memcpy(dest->number, src->number, src->len);
	dest->sign = src->sign;
	dest->lp = src->lp;
	dest->rp = src->rp;
	//dest->len = src->len;
}

fxdpnt *arb_newtonian_div(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	(void)scale; // scale will never be needed
	fxdpnt *guess = arb_expand(NULL, a->len);
	//fxdpnt *newguess = arb_expand(NULL, a->len + b->len);
	fxdpnt *newguess = arb_expand(NULL, 1);
	//fxdpnt *hold = arb_expand(NULL, a->len + b->len);
	fxdpnt *hold = arb_expand(NULL, 1);
	//fxdpnt *hold2 = arb_expand(NULL, a->len + b->len);
	fxdpnt *hold2 = arb_expand(NULL, 1);
	fxdpnt *two = arb_str2fxdpnt("2");;
	fxdpnt *reciprocal;

	guess->lp = 0;
	guess->rp = a->len;
	memset(guess->number, 0, a->len);
	guess->number[a->len -1] = 5;
	guess->len = a->len;

	arb_printold(guess);
	arb_printold(two);
	size_t i = 0;
	while (i < 10)
	{
		//  new_guess = guess * (2 - x * guess);
		hold = arb_mul(b, guess, hold, base); // x * guess
		//arb_printold(a);
		//arb_printold(hold);
		hold2 = arb_sub(two, hold, hold2, base); // 2 - x * guess
		//arb_printold(hold2);
		newguess = arb_mul(guess, hold2, newguess, base); // guess * (2-x*guess)
		arb_copy(guess, newguess);
		arb_printold(newguess);
		//guess = newguess;
		++i;
	}
	reciprocal = guess;
	c = arb_mul(reciprocal, a, c, base);
	return c;
}
