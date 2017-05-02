#include <arbprec/arbprec.h>

bigflt *arbprec_exp(bigflt *x)
{
	size_t j = 30;
	//size_t i = 100;
	//s = (((4 * i) - 2) + ((x * x)/s));

	bigflt *one = str_to_bigflt("1.0000"); 
	bigflt *two = str_to_bigflt("2.0000"); 
	bigflt *four = str_to_bigflt("4.00000");
	bigflt *i = str_to_bigflt("30.00000");
	bigflt *prod = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *prod2 = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *quo = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *z = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *k = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *y = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *sum1 = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *sum2 = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *thou = str_to_bigflt("10000");
	
	
	bigflt *r = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *ret = arbprec_expand_vector(NULL, x->len * 200);
	bigflt *swap;
	
	//bigflt *i = arbprec_expand_vector(NULL, x->len * 200);
	//i = arbprec_mul(x, thou, i);
	//j = i->len * 30;
//	arbprec_print(i);
	
	bigflt *s = str_to_bigflt("1.0");
	s = arbprec_expand_vector(s, x->len * 200); 

	/* precompute r */
	r = arbprec_mul(x, x, r);


	start:
	//arbprec_init(prod);
	//arbprec_init(prod2);
	//arbprec_init(quo); 
//arbprec_print(i);
	prod = arbprec_mul(i, four, prod); 
	prod2 = arbprec_sub(prod, two, prod2);

	quo = arbprec_div(r, s, quo);

	s = arbprec_add(prod2, quo, s);


	--j;
	z = arbprec_sub(i, one, z); 

	swap = i;
	i = z;
	z = swap;
	if ( j >0 )
		goto start;

	/* y = (s + x)/(s - x); */ 
	sum1 = arbprec_add(s, x, sum1);
	sum2 = arbprec_sub(s, x, sum2);
	y = arbprec_div(sum1, sum2, y);
	return y;
	

}
