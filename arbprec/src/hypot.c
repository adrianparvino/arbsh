#include <arbprec/arbprec.h>

bigflt *arbprec_hypot(bigflt *x, bigflt *y)
{

	/*
		hypot.c implemented using the identity:

			hypot(x.y) = sqrt((x*x)+(y*y))
	*/

	bigflt *ret;
	bigflt *pro1 = arbprec_expand_vector(NULL, y->len + x->len);
        bigflt *pro2 = arbprec_expand_vector(NULL, x->len + x->len);
        bigflt *sum = arbprec_expand_vector(NULL, y->len + x->len);


	pro1 = arbprec_mul(x, x, pro1);
	pro2 = arbprec_mul(y, y, pro2);
	sum = arbprec_add(pro1, pro2, sum);
	//ret = arbprec_sqrt(sum);

	return ret;
}
