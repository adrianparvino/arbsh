#include <arbprec/arbprec.h>

bigflt *arbprec_exp(bigflt *a, bigflt *c)
{
	return arbprec_series(a, c, 0);
}

