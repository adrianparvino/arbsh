#include <arbprec/arbprec.h>

/* 
        Exp, sin cos and tan using continued fraction expansion
	(Copyright) 2017, CM. Graff. See LICENSE for copying details
*/ 

fxdpnt *arb_series(fxdpnt *x, fxdpnt *c, int type, int base, int scale)
{

	size_t j = 100;

	fxdpnt *s = arb_str2fxdpnt("1.0");
	fxdpnt *four = arb_str2fxdpnt("4.00000");
	fxdpnt *i = arb_str2fxdpnt("100.00000");
	fxdpnt *two = arb_str2fxdpnt("2.00000");
	fxdpnt *r = arb_expand(NULL, x->len + scale);
	fxdpnt *prod = arb_expand(NULL, x->len + scale);
	fxdpnt *prod2 = arb_expand(NULL, x->len + scale);
	fxdpnt *quo = arb_expand(NULL, x->len + scale);
	fxdpnt *sum1 = arb_expand(NULL, x->len + scale);
	fxdpnt *sum2 = arb_expand(NULL, x->len + scale);
	fxdpnt *negx = arb_expand(NULL, x->len + scale);
	//negx = arb_copy(negx, x);
	memcpy(negx, x, sizeof (ARBT) * x->len);
	//arb_setsign(negx);

	/* precompute r */
	if ( type < 5 && type > 0)
		r = arb_mul(negx, x, r, base);
	else
		r = arb_mul(x, x, r, base);

	start: 

	prod = arb_mul(i, four, prod, base); 
//	arb_short_sub(prod, 2);
	quo = arb_division(r, s, quo, base, scale); 
	s = arb_add(prod, quo, s, base);
//	arb_short_sub(i, 1);
	
	if (--j >0 )
		goto start;

	/* y = (s + x)/(s - x) finishes off exp  */
	if ( type == 0 ) /* exp */
	{
		sum1 = arb_add(s, x, sum1, base);
		sum2 = arb_sub(s, x, sum2, base);
		c = arb_division(sum1, sum2, c, base, scale);
	}
	if ( type == 1 ) /* sin */
	{
		prod2 = arb_mul(two, x, prod2, base);
		sum1 = arb_mul(prod2, s, sum1, base);
		prod = arb_mul(s, s, prod, base);
		sum2 = arb_sub(prod, r, sum2, base);
		c = arb_division(sum1, sum2, c, base, scale);
	}
	if ( type == 2 ) /* cos */
	{
		prod = arb_mul(s, s, prod, base);
		sum1 = arb_add(prod, r, sum1, base);
		prod2 = arb_mul(s, s, prod2, base);
		sum2 = arb_sub(prod2, r, sum2, base);
		c = arb_division(sum1, sum2, c, base, scale);
	}
	if ( type == 3 ) /* tan */
	{
		prod2 = arb_mul(two, x, prod2, base);
		sum1 = arb_mul(prod2, s, sum1, base);
		prod = arb_mul(s, s, prod, base);
		sum2 = arb_add(prod, r, sum2, base);
		c = arb_division(sum1, sum2, c, base, scale);
	}

	arb_free(s);
	arb_free(four);
	arb_free(i);
	arb_free(two);
	arb_free(r);
	arb_free(prod);
	arb_free(prod2);
	arb_free(quo);
	arb_free(sum1);
	arb_free(sum2);
	arb_free(negx);
	
	return c;
}

