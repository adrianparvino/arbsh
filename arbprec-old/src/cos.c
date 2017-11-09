#include <arbprec/arbprec.h> 

bigflt *arbprec_cos(bigflt *a, bigflt *c)
{
	return arbprec_series(a, c, 2);
}

