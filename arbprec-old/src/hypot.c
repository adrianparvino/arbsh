#include <arbprec/arbprec.h>

bigflt *arbprec_hypot(bigflt *x, bigflt *y, bigflt *c)
{

	/*
		hypot.c implemented using the identity:

			hypot(x.y) = sqrt((x*x)+(y*y))
	*/ 
	
	bigflt *pro1 = arbprec_expand_vector(NULL, y->len + x->len);
        bigflt *pro2 = arbprec_expand_vector(NULL, x->len + x->len);
        bigflt *sum = arbprec_expand_vector(NULL, y->len + x->len);

	pro1 = arbprec_mul(x, x, pro1);
	pro2 = arbprec_mul(y, y, pro2);
	sum = arbprec_add(pro1, pro2, sum);
	c = arbprec_sqrt(sum, c);

	arba_free(pro1);
	arba_free(pro2);
	arba_free(sum);

	return c;
}
