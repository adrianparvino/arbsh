#include <arbprec/arbprec.h>

bigflt *arbprec_sqrt(bigflt *x)
{
	size_t i = 0;
	bigflt *y = arbprec_dupa(x);
	bigflt *sum = arbprec_expand_vector(NULL, y->len + x->len);
	bigflt *quo = arbprec_expand_vector(NULL, y->len + x->len);
	bigflt *ret = arbprec_expand_vector(NULL, y->len + x->len); 
	bigflt *two = str_to_bigflt("2");


	start:

	//arbprec_print(x);
//arbprec_print(y);


	quo = arbprec_div(x, y, quo);
//	write(1, "quo\n", 4);
//	arbprec_print(quo);
	
	sum = arbprec_add(quo, y, sum);
//	arbprec_print(sum);
	ret = arbprec_div(sum, two, ret);
//	arbprec_print(ret);
//`	write(1, "\n\n" ,2);


		

	y = ret;
	
	++i;

	if ( i < 20)
		goto start;

	
	return ret;
}
