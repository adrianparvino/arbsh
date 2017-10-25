#include <arbprec/arbprec.h>

/* 
        Exp, sin cos and tan using continued fraction expansion
	(Copyright) 2017, CM. Graff. See LICENSE for copying details
*/ 

bigflt *arbprec_series(bigflt *x, bigflt *c, int type)
{

	size_t j = 100;

	bigflt *s = str_to_bigflt("1.0");
	bigflt *four = str_to_bigflt("4.00000");
	bigflt *i = str_to_bigflt("100.00000");
	bigflt *two = str_to_bigflt("2.00000");
	bigflt *r = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *prod = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *prod2 = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *quo = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *sum1 = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *sum2 = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *negx = arbprec_expand_vector(NULL, x->len + scale);
	negx = arbprec_copy(negx, x);
	arbprec_setsign(negx);

	/* precompute r */
	if ( type < 5 && type > 0)
		r = arbprec_mul(negx, x, r);
	else
		r = arbprec_mul(x, x, r);

	start: 

	prod = arbprec_mul(i, four, prod); 
	arbprec_short_sub(prod, 2);
	quo = arbprec_div(r, s, quo); 
	s = arbprec_add(prod, quo, s);
	arbprec_short_sub(i, 1);
	
	if (--j >0 )
		goto start;

	/* y = (s + x)/(s - x) finishes off exp  */
	if ( type == 0 ) /* exp */
	{
		sum1 = arbprec_add(s, x, sum1);
		sum2 = arbprec_sub(s, x, sum2);
		c = arbprec_div(sum1, sum2, c);
	}
	if ( type == 1 ) /* sin */
	{
		prod2 = arbprec_mul(two, x, prod2);
		sum1 = arbprec_mul(prod2, s, sum1);
		prod = arbprec_mul(s, s, prod);
		sum2 = arbprec_sub(prod, r, sum2);
		c = arbprec_div(sum1, sum2, c);
	}
	if ( type == 2 ) /* cos */
	{
		prod = arbprec_mul(s, s, prod);
		sum1 = arbprec_add(prod, r, sum1);
		prod2 = arbprec_mul(s, s, prod2);
		sum2 = arbprec_sub(prod2, r, sum2);
		c = arbprec_div(sum1, sum2, c);
	}
	if ( type == 3 ) /* tan */
	{
		prod2 = arbprec_mul(two, x, prod2);
		sum1 = arbprec_mul(prod2, s, sum1);
		prod = arbprec_mul(s, s, prod);
		sum2 = arbprec_add(prod, r, sum2);
		c = arbprec_div(sum1, sum2, c);
	}

	arba_free(s);
	arba_free(four);
	arba_free(i);
	arba_free(two);
	arba_free(r);
	arba_free(prod);
	arba_free(prod2);
	arba_free(quo);
	arba_free(sum1);
	arba_free(sum2);
	arba_free(negx);
	
	return c;
}

