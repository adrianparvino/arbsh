#include <arbprec/arbprec.h>

bigflt *arbprec_sin(bigflt *a, bigflt *c)
{
	return arbprec_series(a, c, 1);
}

