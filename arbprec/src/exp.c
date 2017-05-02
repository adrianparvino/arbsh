#include <arbprec/arbprec.h>

bigflt *arbprec_exp(bigflt *x)
{
	/*
                Exp using continued fraction expansion

        */

	size_t j = 30;
	bigflt * s = str_to_bigflt("1.0");
	bigflt *one = str_to_bigflt("1.0000");
	bigflt *two = str_to_bigflt("2.0000");
	bigflt *four = str_to_bigflt("4.00000");
	bigflt *i = str_to_bigflt("30.00000");
	bigflt *z = arbprec_dupa(i);
	bigflt *r = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *prod = arbprec_dupa(r);
	bigflt *prod2 = arbprec_dupa(r);
	bigflt *quo = arbprec_dupa(r);
	bigflt *y = arbprec_dupa(r);
	bigflt *sum1 = arbprec_dupa(r);
	bigflt *sum2 = arbprec_dupa(r);
	bigflt *swap; 
	

	/* precompute r */
	r = arbprec_mul(x, x, r);

	start: 

	prod = arbprec_mul(i, four, prod); 
	prod2 = arbprec_sub(prod, two, prod2); 
	quo = arbprec_div(r, s, quo); 
	s = arbprec_add(prod2, quo, s);
	z = arbprec_sub(i, one, z); 
	swap = i;
	i = z;
	z = swap;

	--j;
	if (j >0 )
		goto start;

	/* y = (s + x)/(s - x) finishes off exp  */
	sum1 = arbprec_add(s, x, sum1);
	sum2 = arbprec_sub(s, x, sum2); 
	y = arbprec_div(sum1, sum2, y);
	
	return y;
}
