#include <arbprec/arbprec.h>

bigflt *arbprec_log(bigflt *x, bigflt *c)
{
	/*
                Log using continued fraction expansion
        */

	size_t j = 90;
	bigflt *s = str_to_bigflt("1.0");
	bigflt *two = str_to_bigflt("2.00000");
	bigflt *i = str_to_bigflt("90.00000");
	bigflt *r = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *prod = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *quo = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *Z = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *ZZ = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *x1 = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *x2 = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *ii = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *iz = arbprec_expand_vector(NULL, x->len + scale);
	bigflt *z2 = arbprec_expand_vector(NULL, x->len + scale);
	

	/* precompute Z and ZZ */
	x1 = arbprec_copy(x1, x);
	x2 = arbprec_copy(x2, x); 
	arbprec_short_sub(x1, 1);
	arbprec_short_add(x2, 1);
	Z = arbprec_div(x1, x2, Z);
	ZZ = arbprec_mul(Z, Z, ZZ);

	start:
	prod = arbprec_mul(i, two, prod);
	arbprec_short_sub(prod, 1);
	ii = arbprec_mul(i, i, ii);
	iz = arbprec_mul(ii, ZZ, iz);
	quo = arbprec_div(iz, s, quo);
	s = arbprec_sub(prod, quo, s);
	arbprec_short_sub(i, 1);
	
	if (--j >0 )
		goto start;
	
	z2 = arbprec_mul(Z, two, z2);
	c = arbprec_div(z2, s, c);
	free(i);
	free(ii);
	free(Z);
	free(ZZ);
	free(prod);
	free(x1);
	free(x2);
	free(z2);
	
	return c;
}