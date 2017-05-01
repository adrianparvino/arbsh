#include <arbprec/arbprec.h>

bigflt *arbprec_sqrt(bigflt *x)
{
	size_t i = 0;

	bigflt *y = arbprec_dupa(x);

	if (x->sign == '-')
	{
		y->nan = 1;
		return y;
	} 

	bigflt *sum = arbprec_expand_vector(NULL, y->len + x->len);
	bigflt *quo = arbprec_expand_vector(NULL, y->len + x->len);
	bigflt *ret = arbprec_expand_vector(NULL, y->len + x->len); 
	bigflt *two = str_to_bigflt("2");

	start:

	quo = arbprec_div(x, y, quo); 
	sum = arbprec_add(quo, y, sum); 
	ret = arbprec_div(sum, two, ret); 
	y = ret;
	
	++i;

	if ( i < 50)
		goto start;
	
	return ret;
}

