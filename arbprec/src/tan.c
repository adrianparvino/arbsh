#include <arbprec/arbprec.h>

bigflt *arbprec_tan(bigflt *a, bigflt *c)
{
	return arbprec_series(a, c, 3);
}


