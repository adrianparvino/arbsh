#include <arbprec/arbprec.h>

bigflt *arbprec_sqrt(bigflt *x, bigflt *c)
{

	/*
		Using Newton's method (Also known as Babylonian sqrt)
			sqrt(x) =  (((x/y) + y) / 2)


	*/
	size_t i = 0;

	arbprec_copy(c, x);

	if (x->sign == '-')
	{
		c->nan = 1;
		return c;
	} 

	bigflt *sum = arbprec_expand_vector(NULL, c->len + x->len);
	bigflt *quo = arbprec_expand_vector(NULL, c->len + x->len);
	bigflt *two = str_to_bigflt("2");

	start:

	quo = arbprec_div(x, c, quo); 
	sum = arbprec_add(quo, c, sum); 
	c = arbprec_div(sum, two, c);

	++i;

	if ( i < 50)
		goto start;

	arba_free(sum);
	arba_free(quo);
	arba_free(two);
	
	return c;
}

